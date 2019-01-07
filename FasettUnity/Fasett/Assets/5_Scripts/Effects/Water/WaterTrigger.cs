using System;
using System.Collections.Generic;
using UnityEngine;

public class WaterTrigger : MonoBehaviour {
    public float PressAmount { private set; get; }

    [SerializeField] private float _riseSpeed;
    [SerializeField] private float _fallSpeed;

    private bool _pressed;

    public Action<WaterTrigger> OnPressedChanged;

    private void OnMouseDrag() {
        _pressed = true;
    }

    private void OnMouseUp() {
        _pressed = false;
    }

    private void Update() {
        if (PressAmount > 0 || _pressed) {
            PressAmount = Mathf.Clamp01(PressAmount + Time.deltaTime / (_pressed ? _riseSpeed : -_fallSpeed));

            if (OnPressedChanged != null) {
                OnPressedChanged(this);
            }
        }
    }

}
