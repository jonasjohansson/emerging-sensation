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

        private bool _calibrating;
        private Effect _currentEffectBeingCalibrated;
        private bool _calibrateNextEffect;

        private WorldAnchorStore _worldAnchorStore;
        private WorldAnchorTransferBatch _worldAnchorTransferBatch;
        private List<byte> _worldAnchorTransferBatchData = new List<byte>(0);

        private AzureFileHandler _azureFileHandler;
        private string _transferBatchFileName = "TransferBatch.dat";
        private string _azureShareName = "hololens";
        private string _azureFolderName = "spatialdata";

#if !UNITY_EDITOR
        private Windows.Storage.StorageFolder _storageFolder;
#endif

        public async void Setup() {
#if !UNITY_EDITOR
            _azureFileHandler = new AzureFileHandler();
            _storageFolder = Windows.Storage.ApplicationData.Current.LocalFolder;
#endif
            // World anchor store might have to be loaded for world anchor actions and transfer batch stuff to work
            WorldAnchorStore.GetAsync(WorldAnchorStoreLoaded);
        }

        private void WorldAnchorStoreLoaded(WorldAnchorStore worldAnchorStore) {
            _worldAnchorStore = worldAnchorStore;
#if !UNITY_EDITOR
            // Attempt to download world anchor transfer batch file from Azure
            _azureFileHandler.DownloadFile(_transferBatchFileName, _storageFolder.Path, _azureShareName, _azureFolderName, DownloadCompleted);
#endif
        }

        private void DownloadCompleted(bool succeeded) {
            Debug.Log("[Effect Manager] Azure download completed with result: " + (succeeded ? "succeeded." : "failed."));
#if !UNITY_EDITOR
            GetTransferBatchFileData();
#endif
        }

#if !UNITY_EDITOR
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
                Debug.Log("[Effect Manager] No transfer batch file found, calibrating all effects.");
                CalibrateAllEffects();
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
            }
            else {
                Debug.Log("[Effect Manager] Deserialization failed or transfer batch is null. Starting calibration.");
                CalibrateAllEffects();
            }
        }

        public void CalibrateAllEffects() {
            if(!_calibrating) {
                StartCoroutine(CalibrateEffectPositions());
            }
        }

        private IEnumerator CalibrateEffectPositions() {
            _calibrating = true;
            _worldAnchorTransferBatch = new WorldAnchorTransferBatch();
            _worldAnchorTransferBatchData.Clear();
            foreach(Effect e in _effects) {
                WorldAnchor existingAnchor = e.GetComponent<WorldAnchor>();
                if (existingAnchor != null) {
                    // Existing world anchors need to be removed before objects can be moved
                    DestroyImmediate(existingAnchor);
                }
                // Place all effects in front of the user for easy grabbing once turned on
                e.transform.SetParent(Camera.main.transform);
                e.transform.position = Camera.main.transform.position + Camera.main.transform.forward * 0.6f;
                e.transform.rotation = Quaternion.identity;
                e.gameObject.SetActive(false);
            }
            foreach (Effect e in _effects) {
                // Turn on effect, deparent from user and let user manipulate with hands
                e.gameObject.SetActive(true);
                e.transform.SetParent(transform);
                e.SetCalibrating(true);
                _currentEffectBeingCalibrated = e;
                _calibrateNextEffect = false;
                TransformByHands transformByHands = e.gameObject.AddComponent<TransformByHands>();
                while (!_calibrateNextEffect) {
                    yield return 0;
                }
                // Positioning done, fix in place and apply a world anchor 
                e.SetCalibrating(false);
                Destroy(transformByHands);
                WorldAnchor anchor = e.gameObject.AddComponent<WorldAnchor>();
                anchor.OnTrackingChanged += Anchor_OnTrackingChanged;
            }
            // All effects positioned, wait a little to allow the last anchor to register, then serialize the world anchor transfer batch
            yield return new WaitForSeconds(1);
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
        }

        private async Task CreateTransferBatchFile(byte[] data) {
            Windows.Storage.StorageFile transferBatchFile = await _storageFolder.CreateFileAsync(_transferBatchFileName, Windows.Storage.CreationCollisionOption.ReplaceExisting);
            IBuffer buffer = data.AsBuffer();
            await Windows.Storage.FileIO.WriteBufferAsync(transferBatchFile, buffer);
            // Transfer batch file created, upload it to Azure
            _azureFileHandler.UploadFile(_transferBatchFileName, _storageFolder.Path, _azureShareName, _azureFolderName, UploadCompleted);
#endif
        }

        private void UploadCompleted() {
            Debug.Log("[Effect Manager] Azure upload completed.");
        }

        public void SetEffectValue(string effectName, float value) {
            foreach(Effect e in _effects) {
                if(e.Name == effectName) {
                    e.SetValue(value);
                }
            }
        }
    }
}
