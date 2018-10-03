using System.Text;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Persistence;
using UnityEngine.XR.WSA.Sharing;
using SimpleFirebaseUnity;

namespace Fasett {
    public class EffectManager : MonoBehaviour {
        [SerializeField] private Effect[] _effects;

        private bool _calibrating;
        private Effect _currentEffectBeingCalibrated;
        private bool _calibrateNextEffect;

        private Firebase _firebase;
        private WorldAnchorStore _worldAnchorStore;
        private WorldAnchorTransferBatch _worldAnchorTransferBatch;
        private List<byte> _worldAnchorTransferBatchData = new List<byte>(0);

        public void Setup() {
            WorldAnchorStore.GetAsync(WorldAnchorStoreLoaded);
        }

        private void WorldAnchorStoreLoaded(WorldAnchorStore worldAnchorStore) {
            _worldAnchorStore = worldAnchorStore;
            GetFirebaseData();
        }

        private void GetFirebaseData() {
            _firebase = Firebase.CreateNew("https://fasett-f1c82.firebaseio.com/", "8D5RgCy6rwZFmKKdfE8EbrD0JmdEjJnz73vdLTcw");
            _firebase.OnGetSuccess += Firebase_GetSucceeded;
            _firebase.OnGetFailed += Firebase_GetFailed;
            _firebase.OnUpdateFailed += Firebase_UpdateFailed;
            _firebase.OnUpdateSuccess += Firebase_UpdateSuccess;
            _firebase.GetValue(FirebaseParam.Empty.OrderByKey().LimitToFirst(2));
        }

        private void Firebase_GetSucceeded(Firebase firebase, DataSnapshot dataSnapshot) {
            Dictionary<string, object> dictionary = (Dictionary<string, object>) dataSnapshot.RawValue;
            string dataString = (string) dictionary["Anchors"];
            byte[] data = Encoding.ASCII.GetBytes(dataString);
            Debug.Log("[Effect Manager] Got data from Firebase, length in kb: " + data.Length / 1024);
#if !UNITY_EDITOR
            WorldAnchorTransferBatch.ImportAsync(data, TransferBatchImportCompleted);
#else
            CalibrateAllEffects();
#endif
        }

        private void Firebase_GetFailed(Firebase firebase, FirebaseError firebaseError) {
            Debug.Log("[Effect Manager] Firebase data retrieval failed with error: " + firebaseError);
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

        private void Firebase_UpdateFailed(Firebase firebase, FirebaseError firebaseError) {
            Debug.Log("[Effect Manager] Updating firebase failed with error: " + firebaseError);
        }

        private void Firebase_UpdateSuccess(Firebase firebase, DataSnapshot dataSnapshot) {
            Debug.Log("[Effect Manager] Updating firebase succeeded!");
        }

        private void TransferBatchExportSerializationCompleted(SerializationCompletionReason serializationCompletionReason) {
            Debug.Log("[Effect Manager] WorldAnchorTransferBatch data serialization completed. Reason: " + serializationCompletionReason);
            byte[] completeData = _worldAnchorTransferBatchData.ToArray();
            string dataString = Encoding.ASCII.GetString(completeData);
            Debug.Log("[Effect Manager] Saving data, total size in kb: " + completeData.Length / 1024);
            _firebase.Child("Anchors").SetValue(dataString, false);
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
