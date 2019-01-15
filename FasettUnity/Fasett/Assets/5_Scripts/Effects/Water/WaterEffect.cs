using System;
using System.Collections.Generic;
using System.Collections;
using UnityEngine;

namespace Fasett { 
    public class WaterEffect : Effect {
        [SerializeField] private RandomSound _audioEffect;

        public float PressAmount { private set; get; }
        public Color Color { private set; get; }
        
        [SerializeField] private AnimationCurve _affectedCurve;
        [SerializeField] private float _duration;
        
        public Action<WaterEffect> OnPressedChanged;
        public Action<WaterEffect> OnTriggered;

        private float _coolDownTime;

        public override void SetColorAsync(Color color) {
            base.SetColorAsync(color);
            Color = color;
        }
        
        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);
            if (value >= 0.5f && _coolDownTime <= 0) {
                _coolDownTime = _duration;
                if (OnTriggered != null) {
                    OnTriggered(this);
                }
            }
        }
        
        protected override void Update() {
            base.Update();
            if (_coolDownTime > 0) {
                _coolDownTime -= Time.deltaTime;
            }
        }

        public void Activate() {
            StopAllCoroutines();
            StartCoroutine(PressedFlow());
        }

        private IEnumerator PressedFlow() {
            _audioEffect.Play();

            float time = 0;
            while (time < 1) {
                time = Mathf.Clamp01(time + Time.deltaTime / _duration);
                PressAmount = _affectedCurve.Evaluate(time);
                if (OnPressedChanged != null) {
                    OnPressedChanged(this);
                }
                yield return 0;
            }
        }

        [ContextMenu("TestColor")]
        private void TestColor() {
            Color = Color.blue;
        }
        
    }
}