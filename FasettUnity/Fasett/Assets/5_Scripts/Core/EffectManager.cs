using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices.WindowsRuntime;
using System.IO;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Persistence;
using UnityEngine.XR.WSA.Sharing;
#if !UNITY_EDITOR
using System.Threading.Tasks;
using Windows.Storage.Streams;
#endif

namespace Fasett {
    public class EffectManager : MonoBehaviour {
        [SerializeField] private Effect[] _effects;

        private WorldAnchorTransferBatch _worldAnchorTransferBatch;
        private List<byte> _worldAnchorTransferBatchData = new List<byte>(0);

        private bool _calibrating;
        private bool _calibrateNextEffect;
        private bool _loadingCalibration;

        private Action<bool, string> _setupCompleteCallback;

        public bool IsCalibrating {
            get {
                return _calibrating || _loadingCalibration;
            }
        }

#if !UNITY_EDITOR
        private AzureFileHandler _azureFileHandler;
        private string _transferBatchFileName = "TransferBatch.dat";
        private Windows.Storage.StorageFolder _storageFolder;
        private string _azureFolderName = "spatialdata";
        private string _azureShareName = "hololens";
#endif

        public async void Setup(Action<bool, string> setupCompleteCallback) {
            _setupCompleteCallback = setupCompleteCallback;
            foreach (Effect e in _effects) {
                e.UpdateEffect(0);
            }
            HideEffects();
#if !UNITY_EDITOR
            await Task.Delay(3000); // Give user time to go to exhibition setup
            _loadingCalibration = true;
            _azureFileHandler = new AzureFileHandler();
            _storageFolder = Windows.Storage.ApplicationData.Current.LocalFolder;
            // World anchor store might have to be loaded for world anchor actions and transfer batch stuff to work
            WorldAnchorStore.GetAsync(WorldAnchorStoreLoaded);
#else
            Invoke("LoadedFromEditor", 5.0f);
#endif
        }

        private void LoadedFromEditor() {
            _setupCompleteCallback(false, "Loading calibration not supported in editor.");
        }

#if !UNITY_EDITOR
        private void WorldAnchorStoreLoaded(WorldAnchorStore worldAnchorStore) {
            // Attempt to download world anchor transfer batch file from Azure
            _azureFileHandler.DownloadFile(_transferBatchFileName, _storageFolder.Path, _azureShareName, _azureFolderName, DownloadCompleted);
        }

        private void DownloadCompleted(bool succeeded) {
            Debug.Log("[Effect Manager] Azure download completed with result: " + (succeeded ? "succeeded." : "failed."));
            if (succeeded) {
                GetTransferBatchFileData();
            }
            else {
                _loadingCalibration = false;
                ShowEffects();
                _setupCompleteCallback(false, "Azure download failed.");
            }
        }

        private async Task GetTransferBatchFileData() {
            if (File.Exists(Path.Combine(_storageFolder.Path, _transferBatchFileName))) {
                Windows.Storage.StorageFile transferBatchFile = await _storageFolder.GetFileAsync(_transferBatchFileName);
                var buffer = await Windows.Storage.FileIO.ReadBufferAsync(transferBatchFile);
                byte[] data = buffer.ToArray();
                Debug.Log("[Effect Manager] Got data from file, length in kb: " + data.Length / 1024);

                // Deserialize the transfer batch data from the file into a world anchor transfer batch object
                WorldAnchorTransferBatch.ImportAsync(data, TransferBatchImportCompleted);
            }
            else {
                Debug.Log("[Effect Manager] No transfer batch file found.");
                _loadingCalibration = false;
                ShowEffects();
                _setupCompleteCallback(false, "Couldn't get transfer batch file from disk.");
            }
        }
#endif

        private void TransferBatchImportCompleted(SerializationCompletionReason serializationCompletionReason, WorldAnchorTransferBatch worldAnchorTransferBatch) {
            Debug.Log("[Effect Manager] Deserialization of world anchor transfer batch completed, result: " + serializationCompletionReason);
            if(worldAnchorTransferBatch != null && serializationCompletionReason == SerializationCompletionReason.Succeeded) {
                foreach(Effect e in _effects) {
                    worldAnchorTransferBatch.LockObject(e.Name, e.gameObject);
                    Debug.Log("[Effect Manager] Locked effect " + e.Name + " to world anchor imported from transfer batch.");
                }
                _loadingCalibration = false;
                ShowEffects();
                _setupCompleteCallback(true, "Calibration successfully loaded!");
            }
            else {
                Debug.Log("[Effect Manager] Deserialization failed or transfer batch is null.");
                _loadingCalibration = false;
                ShowEffects();
                _setupCompleteCallback(false, "Transfer batch deserialization failed or result is null.");
            }
        }

        public void CalibrateAllEffects() {
            if(!IsCalibrating) {
                StartCoroutine(CalibrateAllEffectsCoroutine());
            }
        }

        public void CalibrateClosestEffect() {
            if(!IsCalibrating) {
                StartCoroutine(CalibrateClosestEffectCoroutine());
            }
        }

        private IEnumerator CalibrateAllEffectsCoroutine() {
            _calibrating = true;
            PrepareWorldAnchorTransferBatch();
            foreach(Effect e in _effects) {
                PrepareEffectForCalibration(e);
            }
            foreach (Effect e in _effects) {
                yield return CalibrateEffectCoroutine(e);
            }
            // All effects positioned, wait a little to allow all anchors to register, then serialize the world anchor transfer batch
            AnchorAllEffects();
            yield return new WaitForSeconds(1);
            ConcludeCalibration();
        }

        private IEnumerator CalibrateClosestEffectCoroutine() {
            _calibrating = true;
            PrepareWorldAnchorTransferBatch();
            Effect closest = null;
            float closestDistance = Mathf.Infinity;
            foreach (Effect effect in _effects) {
                float effectDistance = Vector3.Distance(Camera.main.transform.position, effect.transform.position);
                if (effectDistance < closestDistance) {
                    closestDistance = effectDistance;
                    closest = effect;
                }
            }
            PrepareEffectForCalibration(closest, false);
            yield return CalibrateEffectCoroutine(closest);
            AnchorAllEffects();
            yield return new WaitForSeconds(1);
            ConcludeCalibration();
        }

        private void PrepareEffectForCalibration(Effect effect, bool move = true) {
            WorldAnchor existingAnchor = effect.GetComponent<WorldAnchor>();
            if(existingAnchor != null) {
                // Existing world anchors need to be removed before objects can be moved
                DestroyImmediate(existingAnchor);
            }
            // Place all effects in front of the user for easy grabbing once turned on
            if (move) {
                effect.transform.SetParent(Camera.main.transform);
                effect.transform.position = Camera.main.transform.position + Camera.main.transform.forward * 0.6f;
                effect.transform.rotation = Quaternion.identity;
            }
            effect.gameObject.SetActive(false);
        }

        private IEnumerator CalibrateEffectCoroutine(Effect effect) {
            Debug.Log($"[Effect Manager] Calibrating effect {effect.Name}.");
            // Turn on effect, deparent from user and let user manipulate with hands
            effect.gameObject.SetActive(true);
            effect.transform.SetParent(transform);
            effect.SetCalibrating(true);
            _calibrateNextEffect = false;
            TransformByHands transformByHands = effect.gameObject.AddComponent<TransformByHands>();
            bool increasing = true;
            float effectValue = 0;
            while(!_calibrateNextEffect) {
                // Pulsate effect
                if(increasing) {
                    effectValue += Time.deltaTime;
                    if(effectValue >= 1.0f) {
                        effectValue = 1.0f;
                        increasing = false;
                    }
                }
                else {
                    effectValue -= Time.deltaTime;
                    if(effectValue <= 0.0f) {
                        effectValue = 0.0f;
                        increasing = true;
                    }
                }
                effect.UpdateEffect(Mathf.Clamp01(effectValue));
                yield return 0;
            }
            // Positioning done, fix in place and apply a world anchor 
            effect.SetCalibrating(false);
            effect.UpdateEffect(0);
            Destroy(transformByHands);
            Debug.Log($"[Effect Manager] Done calibrating effect {effect.Name}.");
        }

        private void ConcludeCalibration() {
#if !UNITY_EDITOR
            WorldAnchorTransferBatch.ExportAsync(_worldAnchorTransferBatch, TransferBatchExportDataAvailable, TransferBatchExportSerializationCompleted);
#endif
            _calibrating = false;
        }

        public void CalibrateNextEffect() {
            if(_calibrating) {
                _calibrateNextEffect = true;
            }
        }

        private void PrepareWorldAnchorTransferBatch() {
            _worldAnchorTransferBatch = new WorldAnchorTransferBatch();
            _worldAnchorTransferBatchData.Clear();
        }

        private void AnchorAllEffects() {
            foreach (Effect effect in _effects) {
                WorldAnchor anchor = effect.gameObject.GetComponent<WorldAnchor>();
                if (anchor ==  null) {
                    anchor = effect.gameObject.AddComponent<WorldAnchor>();
                }
                anchor.OnTrackingChanged += Anchor_OnTrackingChanged;
            }
        }

        private void Anchor_OnTrackingChanged(WorldAnchor worldAnchor, bool located) {
            // World anchor registered, add it to the transfer batch
            _worldAnchorTransferBatch.AddWorldAnchor(worldAnchor.GetComponent<Effect>().Name, worldAnchor);
            worldAnchor.OnTrackingChanged -= Anchor_OnTrackingChanged;
        }

        private void TransferBatchExportDataAvailable(byte[] data) {
            Debug.Log("[Effect Manager] Finished serializing some data, length: " + data.Length);
            _worldAnchorTransferBatchData.AddRange(data);
        }

        private void TransferBatchExportSerializationCompleted(SerializationCompletionReason serializationCompletionReason) {
            Debug.Log("[Effect Manager] WorldAnchorTransferBatch data serialization completed. Result: " + serializationCompletionReason);
            byte[] completeData = _worldAnchorTransferBatchData.ToArray();
            Debug.Log("[Effect Manager] Saving data to file, total size in kb: " + completeData.Length / 1024);
#if !UNITY_EDITOR
            CreateTransferBatchFile(completeData);
#endif
        }

#if !UNITY_EDITOR
        private async Task CreateTransferBatchFile(byte[] data) {
            Windows.Storage.StorageFile transferBatchFile = await _storageFolder.CreateFileAsync(_transferBatchFileName, Windows.Storage.CreationCollisionOption.ReplaceExisting);
            IBuffer buffer = data.AsBuffer();
            await Windows.Storage.FileIO.WriteBufferAsync(transferBatchFile, buffer);
            // Transfer batch file created, upload it to Azure
            _azureFileHandler.UploadFile(_transferBatchFileName, _storageFolder.Path, _azureShareName, _azureFolderName, UploadCompleted);
        }

        private void UploadCompleted() {
            Debug.Log("[Effect Manager] Azure upload completed.");
        }
#endif

        public void SetEffectValueAsync(string effectName, float value) {
            if (!_calibrating) {
                foreach(Effect e in _effects) {
                    if(e.Name == effectName) {
                        e.SetValueAsync(value);
                    }
                }
            }
        }

        public void HideEffects() {
            foreach (Effect e in _effects) {
                e.HideEffect();
            }
        }

        public void ShowEffects() {
            foreach(Effect e in _effects) {
                e.ShowEffect();
            }
        }
    }
}
