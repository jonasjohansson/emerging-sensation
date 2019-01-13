using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

namespace Fasett {
    public class EffectController : MonoBehaviour {
        [SerializeField] private DistanceFade _distanceFade;
        [SerializeField] private int _updateInterval = 3;
        protected Effect[] _effects;

        protected virtual void Awake() {
            _effects = GetComponentsInChildren<Effect>(false);
            _distanceFade.OnVisibilityChanged += VisibilityChanged;
        }

        protected virtual void VisibilityChanged(float visibility) {
            for (int i = 0; i < _effects.Length; i++) {
                _effects[i].SetVisibility(visibility);
            }
        }

        protected virtual void OnEnable() {
            StartCoroutine(CenterEverySeconds(_updateInterval));
        }

        private IEnumerator CenterEverySeconds(int seconds) {
            while (true) {
                Vector3 center = GetCenterPoint();
                CenterObjects(center);
                yield return new WaitForSeconds(seconds);
            }
        }

        protected virtual void CenterObjects(Vector3 center) {
            _distanceFade.transform.position = center;
        }

        private Vector3 GetCenterPoint() {
            Vector3 sum = Vector3.zero;
            if (_effects == null || _effects.Length == 0) {
                return sum;
            }

            foreach (var trigger in _effects) {
                sum += trigger.transform.position;
            }
            return sum / _effects.Length;
        }
    }
}