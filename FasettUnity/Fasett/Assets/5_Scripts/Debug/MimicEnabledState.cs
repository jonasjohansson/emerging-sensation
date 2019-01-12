using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Fasett {
    [ExecuteInEditMode]
    public class MimicEnabledState : MonoBehaviour {
        [SerializeField] private Renderer _renderer;
        [SerializeField] private GameObject _target;

        private void Update() {
            _renderer.enabled = _target.activeInHierarchy;
        }

        [ContextMenu("Setup")]
        private void Setup() {
            _renderer = GetComponent<Renderer>();
            name = _target.name;
        }
    }
}
