using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Persistence;
using UnityEngine.XR.WSA.Sharing;

namespace Fasett {
    public class HololensDebug : MonoBehaviour {
        [SerializeField] private TextMesh _text;
        [SerializeField] private GameObject[] _debugObjects;

        private bool _debugging = false;

        private void Awake() {
            ToggleDebug();
        }

        private void OnEnable() {
            UserInput.OnUserSaidDebug += ToggleDebug;
        }
        private void OnDisable() {
            UserInput.OnUserSaidDemoMode -= ToggleDebug;
        }

        private void ToggleDebug() {
            _debugging = !_debugging;
            _text.text = _debugging ? "DEBUG" : "";
            foreach (GameObject go in _debugObjects) {
                go.SetActive(_debugging);
            }
        }
    
    }
}
