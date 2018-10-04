using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class Effect : MonoBehaviour {
        [SerializeField] protected string _effectName;
        [SerializeField] protected GameObject _calibrationView;
        private float _latestValue;
        private float _oldValue;

        protected virtual void Awake() {
            _calibrationView.SetActive(false);
        }

        protected virtual void Update() {
            if (_latestValue != _oldValue) {
                UpdateEffect(_latestValue);
            }
        }

        public void SetCalibrating(bool state) {
            _calibrationView.SetActive(state);
        }

        public string Name { get { return _effectName; } }

        public virtual void SetValueAsync(float value) {
            _latestValue = value;
        }

        public virtual void UpdateEffect(float value) {
            _oldValue = value;
            _latestValue = value;
        }
    }
}
