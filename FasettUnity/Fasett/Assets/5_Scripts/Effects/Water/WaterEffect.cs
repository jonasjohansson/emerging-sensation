using System;
using System.Collections.Generic;
using UnityEngine;
using Fasett;

public class WaterEffect : Effect {
    public float PressAmount { private set; get; }
    public Color Color { private set; get; }

    [SerializeField] private float _riseSpeed;
    [SerializeField] private float _fallSpeed;

    private bool _pressed;

    public Action<WaterEffect> OnPressedChanged;

    private void OnMouseDrag() {
        _pressed = true;
    }

    private void OnMouseUp() {
        _pressed = false;
    }

    public override void SetColorAsync(Color color) {
        base.SetColorAsync(color);
        Color = color;
    }

    public override void UpdateEffect(float value) {
        base.UpdateEffect(value);
        _pressed = value > 0.5f;
    }

    protected override void Update() {
        base.Update();
    
        if (PressAmount > 0 || _pressed) {
            PressAmount = Mathf.Clamp01(PressAmount + Time.deltaTime / (_pressed ? _riseSpeed : -_fallSpeed));

            if (OnPressedChanged != null) {
                OnPressedChanged(this);
            }
        }
    }

}
