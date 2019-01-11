using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett { 
    public class SplittingCell : Effect {
        [SerializeField] private Animator _animator;
        [SerializeField] private float _coolDown = 1;

        private float _coolDownTime;

        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);
            if (_coolDownTime > 0) {
                _coolDownTime -= Time.deltaTime;
            }

            if (value >= 0.5f && _coolDownTime <= 0) {
                _animator.SetTrigger("Activate");
                _coolDownTime = _coolDown;
            }
        }

        protected override void Update() {
            base.Update();
        }
    }
}
