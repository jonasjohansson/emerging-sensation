using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA.Input;

namespace Fasett {
    public class EffectManager : MonoBehaviour {
        [SerializeField] private Effect[] _effects;

        private Effect _currentlyCalibratingEffect;
        private bool _next;
        private GameObject _grabbingHand;
        private Vector3 _grabbingHandStartPosition;

        public void Setup() {
            // Check if calibrated before
            // ELSE
            // Stop accepting messages
            foreach(Effect e in _effects) {
                e.SetValue(0);
                e.transform.SetParent(Camera.main.transform);
                e.transform.position = Camera.main.transform.position + Camera.main.transform.forward * 0.6f;
            }
            StartCoroutine(Calibrate());
        }

        public void SetEffectValue(string effectName, float value) {
            foreach (Effect e in _effects) {
                if (e.Name == effectName) {
                    e.SetValue(value);
                }
            }
        }

        private IEnumerator Calibrate() {
            GestureRecognizer recognizer = new GestureRecognizer();
            recognizer.SetRecognizableGestures(GestureSettings.Tap | GestureSettings.ManipulationTranslate);
            recognizer.ManipulationStarted += StartMoveEffect;
            recognizer.ManipulationUpdated += UpdateMoveEffect;
            recognizer.ManipulationCompleted += CompleteMoveEffect;
            recognizer.StartCapturingGestures();

            foreach (Effect e in _effects) {
                e.SetValue(1);
                e.transform.SetParent(transform);
                _currentlyCalibratingEffect = e;
                _next = false;
                while (!_next) {
                    yield return 0;
                }
                e.SetValue(0);
            }
            recognizer.ManipulationStarted -= StartMoveEffect;
            recognizer.ManipulationUpdated -= UpdateMoveEffect;
            recognizer.ManipulationCompleted -= CompleteMoveEffect;
            recognizer.StopCapturingGestures();
            recognizer = null;
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
    }
}
