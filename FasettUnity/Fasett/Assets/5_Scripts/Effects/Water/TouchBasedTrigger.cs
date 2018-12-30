using System;
using System.Collections.Generic;
using UnityEngine;

public class TouchBasedTrigger : MonoBehaviour {
    [SerializeField] private float _riseSpeed;
    [SerializeField] private float _fallSpeed;

    private bool _pressed;
    private float _pressAmount;

    public Action<float> OnPressedChanged;

    private void OnMouseDrag() {
        _pressed = true;
    }

    private void OnMouseUp() {
        _pressed = false;
    }

    private void Update() {
        if (_pressAmount > 0 || _pressed) {
            _pressAmount = Mathf.Clamp01(_pressAmount + Time.deltaTime / (_pressed ? _riseSpeed : -_fallSpeed));

            if (OnPressedChanged != null) {
                OnPressedChanged(_pressAmount);
            }
        }
    }

}
