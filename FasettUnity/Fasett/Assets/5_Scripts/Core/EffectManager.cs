using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Input;
using UnityEngine.Windows.Speech;
using UnityEngine.XR.WSA.Persistence;

namespace Fasett {
    public class EffectManager : MonoBehaviour {
        [SerializeField] private Effect[] _effects;
        private WorldAnchorStore _worldAnchorStore;

        private bool _calibrating;
        private Effect _currentEffectBeingCalibrated;
        private bool _calibrateNextEffect;

        public void Setup() {
            WorldAnchorStore.GetAsync(WorldAnchorStoreLoaded);
        }

        public void SetEffectValue(string effectName, float value) {
            foreach (Effect e in _effects) {
                if (e.Name == effectName) {
                    e.SetValue(value);
                }
            }
        }

        private void WorldAnchorStoreLoaded(WorldAnchorStore store) {
            _worldAnchorStore = store;
            Debug.Log("World anchor store loaded, containing " + _worldAnchorStore.anchorCount + " anchors.");

            if(_worldAnchorStore.anchorCount > 0) {
                foreach (Effect e in _effects) {
                    _worldAnchorStore.Load(e.Name, e.gameObject);
                }
            }
            else {
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

            _worldAnchorStore.Clear();

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
                if (_worldAnchorStore != null) {
                    WorldAnchor anchor = e.gameObject.AddComponent<WorldAnchor>();
                    anchor.OnTrackingChanged += Anchor_OnTrackingChanged;
                }
            }

            yield return new WaitForSeconds(1);
            Debug.Log("Calibration complete, world anchor store now contains " + _worldAnchorStore.anchorCount + " anchors.");

            _calibrating = false;
        }

        private void Anchor_OnTrackingChanged(WorldAnchor worldAnchor, bool located) {
            bool succeeded = _worldAnchorStore.Save(worldAnchor.GetComponent<Effect>().Name, worldAnchor);
            Debug.Log(succeeded ? "Saving anchor succeeded." : "Saving anchor failed.");
            Debug.Log("Number of anchors in world anchor store: " + _worldAnchorStore.anchorCount);
            worldAnchor.OnTrackingChanged -= Anchor_OnTrackingChanged;
        }

        public void CalibrateNextEffect() {
            if (_calibrating) {
                _calibrateNextEffect = true;
            }
        }
    }
}
