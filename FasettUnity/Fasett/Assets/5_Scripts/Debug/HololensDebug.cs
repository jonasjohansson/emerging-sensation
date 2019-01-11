using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Persistence;
using UnityEngine.XR.WSA.Sharing;

namespace Fasett {
    public class HololensDebug : MonoBehaviour {
        [SerializeField] private TextMesh _text;
        [SerializeField] private LineRenderer _line;
        [SerializeField] private Transform[] _objects;

        private bool _debugging = true;

        private void OnEnable() {
            UserInput.OnUserSaidDebug += ToggleDebug;
        }
        private void OnDisable() {
            UserInput.OnUserSaidDemoMode -= ToggleDebug;
        }

        private void Update() {
            if (_debugging) {
                Vector3[] positions = new Vector3[_objects.Length];
                for (int i = 0; i < _objects.Length; i++) {
                    positions[i] = _objects[i].position;
                }
                _line.SetPositions(positions);
            }
        }

        private void ToggleDebug() {
            _debugging = !_debugging;
            _text.text = _debugging ? "DEBUG" : "";
        }
    
    }
}
