using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class Effect : MonoBehaviour {
        [SerializeField] protected string _effectName;
        [SerializeField] protected GameObject _calibrationView;

        protected virtual void Awake() {
            _calibrationView.SetActive(false);
        }

        public void SetCalibrating(bool state) {
            _calibrationView.SetActive(state);
        }

        public string Name { get { return _effectName; } }

        public virtual void SetValue(float value) { }
    }
}
