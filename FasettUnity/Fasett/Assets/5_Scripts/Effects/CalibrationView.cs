using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA.Input;

namespace Fasett {
    public class CalibrationView : MonoBehaviour {
        [SerializeField] protected GameObject _calibrationView;
        [SerializeField] protected TextMesh _text;

        private Color _textColor;

        private void Awake() {
            _textColor = _text.color;
        }

        public void SetActive(bool shouldBeActive) {
            _calibrationView.SetActive(shouldBeActive);
        }

        private void OnEnable() {
            InteractionManager.InteractionSourcePressed += IsMoving;
            InteractionManager.InteractionSourceReleased += IsNotMoving;
        }

        private void OnDisable() {
            InteractionManager.InteractionSourcePressed -= IsMoving;
            InteractionManager.InteractionSourceReleased -= IsNotMoving;
        }


        public void IsMoving(InteractionSourcePressedEventArgs args) {
            _text.color = Color.yellow ;
        }
        
        public void IsNotMoving(InteractionSourceReleasedEventArgs args) {
            _text.color = _textColor;
        }

        [ContextMenu("Setup")]
        private void Setup() {
            _text = GetComponentInChildren<TextMesh>();
            _calibrationView = gameObject;
        }
    }
}
