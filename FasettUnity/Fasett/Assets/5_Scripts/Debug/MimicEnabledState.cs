using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.XR.WSA;

namespace Fasett {
    [ExecuteInEditMode]
    public class MimicEnabledState : MonoBehaviour {
        [SerializeField] private Renderer _renderer;
        [SerializeField] private GameObject _target;

        private WorldAnchor _worldAnchor;

        private void OnEnable() {
            _worldAnchor = _target.GetComponent<WorldAnchor>();
        }

        private void Update() {
            _renderer.enabled = _target.activeInHierarchy;
            if (_worldAnchor) {
                Color color = _worldAnchor.isLocated ? Color.green : Color.gray;
                _renderer.material.SetColor("_Color", color);
            }
        }

        [ContextMenu("Setup")]
        private void Setup() {
            _renderer = GetComponent<Renderer>();
            name = _target.name;
        }
    }
}
