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

        private Effect _currentlyCalibratingEffect;
        private bool _next;
        private GameObject _grabbingHand;
        private Vector3 _grabbingHandStartPosition;

        public void Setup() {
            WorldAnchorStore.GetAsync(StoreLoaded);
        }

        public void SetEffectValue(string effectName, float value) {
            foreach (Effect e in _effects) {
                if (e.Name == effectName) {
                    e.SetValue(value);
                }
            }
        }

        private void StoreLoaded(WorldAnchorStore store) {
            _worldAnchorStore = store;

            Debug.Log("World anchor store loaded, containing " + _worldAnchorStore.anchorCount + " anchors.");

            if(_worldAnchorStore.anchorCount > 0) {
                foreach (Effect e in _effects) {
                    _worldAnchorStore.Load(e.Name, e.gameObject);
                }
            }
            else {
                foreach(Effect e in _effects) {
                    e.SetValue(0);
                    e.transform.SetParent(Camera.main.transform);
                    e.transform.position = Camera.main.transform.position + Camera.main.transform.forward * 0.6f;
                }
                StartCoroutine(Calibrate());
            }
        }

        private IEnumerator Calibrate() {
            GestureRecognizer recognizer = new GestureRecognizer();
            recognizer.SetRecognizableGestures(GestureSettings.Tap | GestureSettings.ManipulationTranslate);
            recognizer.ManipulationStarted += StartMoveEffect;
            recognizer.ManipulationUpdated += UpdateMoveEffect;
            recognizer.ManipulationCompleted += CompleteMoveEffect;
            recognizer.StartCapturingGestures();

            KeywordRecognizer keywordRecognizer;
            keywordRecognizer = new KeywordRecognizer(new string[] { "next" });
            keywordRecognizer.OnPhraseRecognized += PhraseRecognized;
            keywordRecognizer.Start();

            foreach (Effect e in _effects) {
                e.SetValue(1);
                e.transform.SetParent(transform);
                _currentlyCalibratingEffect = e;
                _next = false;
                while (!_next) {
                    yield return 0;
                }
                e.SetValue(0);
                if (_worldAnchorStore != null) {
                    WorldAnchor anchor = e.gameObject.AddComponent<WorldAnchor>();
                    _worldAnchorStore.Save(e.Name, anchor);
                }
            }
            recognizer.ManipulationStarted -= StartMoveEffect;
            recognizer.ManipulationUpdated -= UpdateMoveEffect;
            recognizer.ManipulationCompleted -= CompleteMoveEffect;
            recognizer.StopCapturingGestures();
            recognizer = null;

            keywordRecognizer.OnPhraseRecognized -= PhraseRecognized;
            keywordRecognizer.Stop();
            keywordRecognizer = null;

            // Debug see where all effects are
            foreach(Effect e in _effects) {
                e.SetValue(1);
            }
            Debug.Log("Calibration complete, world anchor store now contains " + _worldAnchorStore.anchorCount + " anchors.");
        }

        private void StartMoveEffect(ManipulationStartedEventArgs eventArgs) {
            Vector3 handPosition;
            eventArgs.sourcePose.TryGetPosition(out handPosition);
            _grabbingHand = new GameObject("Grabbing Hand");
            _grabbingHand.transform.position = handPosition;
            _grabbingHandStartPosition = handPosition;
            _grabbingHand.transform.rotation = Camera.main.transform.rotation;
            _currentlyCalibratingEffect.transform.SetParent(_grabbingHand.transform);
        }

        private void UpdateMoveEffect(ManipulationUpdatedEventArgs eventArgs) {
            Vector3 handPosition;
            eventArgs.sourcePose.TryGetPosition(out handPosition);
            _grabbingHand.transform.position = _grabbingHandStartPosition + eventArgs.cumulativeDelta;
            _grabbingHand.transform.rotation = Camera.main.transform.rotation;
        }

        private void CompleteMoveEffect(ManipulationCompletedEventArgs eventArgs) {
            _currentlyCalibratingEffect.transform.SetParent(transform);
            Destroy(_grabbingHand);
        }

        private void CancelMoveEffect(ManipulationCanceledEventArgs eventArgs) {
            _currentlyCalibratingEffect.transform.SetParent(transform);
            Destroy(_grabbingHand);
        }

        private void PhraseRecognized(PhraseRecognizedEventArgs eventArgs) {
            if (eventArgs.text == "next") {
                _next = true;
            }
        }
    }
}
