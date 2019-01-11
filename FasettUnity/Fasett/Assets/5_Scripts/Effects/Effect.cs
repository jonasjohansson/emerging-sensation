using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class Effect : MonoBehaviour {
        public string Name { get { return _effectName; } }
        [SerializeField] protected string _effectName;

        [SerializeField] protected GameObject _calibrationView;
        public Transform OriginalParent { get; private set; }

        private float _latestValue;
        private float _oldValue;

        private Color _latestColor;
        private Color _oldColor;

        protected virtual void Awake() {
            OriginalParent = transform.parent;
            _calibrationView.SetActive(false);
        }

        protected virtual void Update() {
            if (_latestValue != _oldValue) {
                UpdateEffect(_latestValue);
            }
            if (_latestColor != _oldColor) {
                UpdateColor(_latestColor);
            }
        }

        public void SetCalibrating(bool state) {
            _calibrationView.SetActive(state);
        }


        public virtual void SetValueAsync(float value) {
            _latestValue = value;
        }
        public virtual void SetColorAsync(Color color) {
            _latestColor = color;
        }

        public virtual void UpdateEffect(float value) {
            _latestValue = value;
            _oldValue = value;
        }

        public virtual void UpdateColor(Color color) {
            _oldColor = color;
            _latestColor = color;
        }

        public void HideEffect() {
            Debug.Log("Hiding effect " + Name);
            gameObject.SetActive(false);
        }

        public void ShowEffect() {
            Debug.Log("Showing effect " + Name);
            gameObject.SetActive(true);
        }
    }
}
