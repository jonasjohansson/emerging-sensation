using System;
using System.Collections.Generic;
using UnityEngine;
using Fasett;

public class WaterEffect : Effect {
    public float PressAmount { private set; get; }
    public Color Color { private set; get; }

    [SerializeField] private float _riseSpeed;
    [SerializeField] private float _fallSpeed;

    [SerializeField] private AnimationCurve _riseCurve;
    [SerializeField] private AnimationCurve _fallCurve;

    private bool _pressed;
    private float _currentPress;

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
    
        if (_currentPress > 0 || _pressed) {
            if (_pressed) { 
                _currentPress = Mathf.Clamp01(_currentPress + Time.deltaTime /_riseSpeed);
                PressAmount = _riseCurve.Evaluate(_currentPress); 
            }
            else {
                _currentPress = Mathf.Clamp01(_currentPress + Time.deltaTime / -_fallSpeed);
                PressAmount = _fallCurve.Evaluate(_currentPress);
            }

            if (OnPressedChanged != null) {
                OnPressedChanged(this);
            }
        }
    }

    [ContextMenu("TestColor")]
    private void TestColor() {
        Color = Color.blue;
    }

}
