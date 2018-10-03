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

        private string _transferBatchFileName = "TransferBatch.dat";

        private AzureFileHandler _azureFileHandler;

#if !UNITY_EDITOR
        private Windows.Storage.StorageFolder _storageFolder;
#endif

        public async void Setup() {
            // Test azure
#if !UNITY_EDITOR
            string fileName = "HololensTest.txt";
            _storageFolder = Windows.Storage.ApplicationData.Current.LocalFolder;
            Windows.Storage.StorageFile testFile = await _storageFolder.CreateFileAsync(fileName, Windows.Storage.CreationCollisionOption.ReplaceExisting);
            _azureFileHandler = new AzureFileHandler();
            _azureFileHandler.UploadFile(fileName, _storageFolder.Path, "HololensShare", "HololensFolder", UploadCompleted);
#endif
            WorldAnchorStore.GetAsync(WorldAnchorStoreLoaded);

        }

        private void UploadCompleted() {
            Debug.Log("[Effect Manager] Upload completed.");
#if !UNITY_EDITOR
            _azureFileHandler.DownloadFile("HololensTest.txt", _storageFolder.Path, "HololensShare", "HololensFolder", DownloadCompleted);
#endif
        }

        private void DownloadCompleted() {
            Debug.Log("[Effect Manager] Download completed.");
        }

        private void WorldAnchorStoreLoaded(WorldAnchorStore worldAnchorStore) {
            _worldAnchorStore = worldAnchorStore;
#if !UNITY_EDITOR
            //GetFileData();
        }

        private async Task GetFileData() {
            if (File.Exists(Path.Combine(_storageFolder.Path, _transferBatchFileName))) {
                Windows.Storage.StorageFile transferBatchFile = await _storageFolder.GetFileAsync(_transferBatchFileName);
                var buffer = await Windows.Storage.FileIO.ReadBufferAsync(transferBatchFile);
                byte[] data = buffer.ToArray();
                Debug.Log("[Effect Manager] Got data from file, length in kb: " + data.Length / 1024);
                WorldAnchorTransferBatch.ImportAsync(data, TransferBatchImportCompleted);
            }
            else {
                Debug.Log("[Effect Manager] No transfer batch file found, calibrating all effects.");
                CalibrateAllEffects();
            }
#endif
        }

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

            foreach(Effect e in _effects) {
                WorldAnchor existingAnchor = e.GetComponent<WorldAnchor>();
                if (existingAnchor != null) {
                    DestroyImmediate(existingAnchor);
                }
                e.transform.SetParent(Camera.main.transform);
                e.transform.position = Camera.main.transform.position + Camera.main.transform.forward * 0.6f;
                e.transform.rotation = Quaternion.identity;
                e.gameObject.SetActive(false);
            }

            foreach (Effect e in _effects) {
                e.gameObject.SetActive(true);
                e.transform.SetParent(transform);
                e.SetCalibrating(true);
                _currentEffectBeingCalibrated = e;
                _calibrateNextEffect = false;
                TransformByHands transformByHands = e.gameObject.AddComponent<TransformByHands>();
                while (!_calibrateNextEffect) {
                    yield return 0;
                }
                e.SetCalibrating(false);
                Destroy(transformByHands);
                WorldAnchor anchor = e.gameObject.AddComponent<WorldAnchor>();
                anchor.OnTrackingChanged += Anchor_OnTrackingChanged;
            }

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
            _worldAnchorTransferBatch.AddWorldAnchor(worldAnchor.GetComponent<Effect>().Name, worldAnchor);
            worldAnchor.OnTrackingChanged -= Anchor_OnTrackingChanged;
        }

        private void TransferBatchExportDataAvailable(byte[] data) {
            Debug.Log("[Effect Manager] Finished serializing some data, length: " + data.Length);
            _worldAnchorTransferBatchData.AddRange(data);
        }

        private void TransferBatchExportSerializationCompleted(SerializationCompletionReason serializationCompletionReason) {
            Debug.Log("[Effect Manager] WorldAnchorTransferBatch data serialization completed. Reason: " + serializationCompletionReason);
            byte[] completeData = _worldAnchorTransferBatchData.ToArray();
            Debug.Log("[Effect Manager] Saving data, total size in kb: " + completeData.Length / 1024);
#if !UNITY_EDITOR
            CreateTransferBatchFile(completeData);
        }

        private async Task CreateTransferBatchFile(byte[] data) {
            Windows.Storage.StorageFile transferBatchFile = await _storageFolder.CreateFileAsync(_transferBatchFileName, Windows.Storage.CreationCollisionOption.ReplaceExisting);
            IBuffer buffer = data.AsBuffer();
            await Windows.Storage.FileIO.WriteBufferAsync(transferBatchFile, buffer);
#endif
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
