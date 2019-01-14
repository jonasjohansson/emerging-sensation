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
        [SerializeField] private SpatialMappingToggle _spatialMappingToggle;

        [SerializeField] private bool _disableBlockersInEditor;

        private bool _debugging = false;

        private void Awake() {
            // this sets debugging to false at start
            _debugging = true;
            ToggleDebug();
            if (Application.isEditor && _disableBlockersInEditor) {
                DistanceFade.ShouldBeActive = false;
            }
        }

        private void OnEnable() {
            UserInput.OnUserSaidDebug += ToggleDebug;
            UserInput.OnUserSaidWireframe += ShowWireFrame;
        }
        private void OnDisable() {
            UserInput.OnUserSaidDemoMode -= ToggleDebug;
            UserInput.OnUserSaidWireframe += ShowWireFrame;
        }

        private void Update() {
            if (_debugging) {
                _text.text = "Tracking: " + WorldManager.state.ToString();
            }
        }

        private void ToggleDebug() {
            _debugging = !_debugging;
            _text.text = _debugging ? "DEBUG" : "";
            foreach (GameObject go in _debugObjects) {
                go.SetActive(_debugging);
            }
        }

        private void ShowWireFrame() {
            _spatialMappingToggle.ToggleRendering();
        }

    }
}
