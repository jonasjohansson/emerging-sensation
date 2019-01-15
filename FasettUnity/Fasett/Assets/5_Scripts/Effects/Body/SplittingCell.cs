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

            if (value >= 0.5f && _coolDownTime <= 0) {
                _animator.SetTrigger("Activate");
                _coolDownTime = _coolDown;
            }
        }

        public override void SetVisibility(float visibility) {
            base.SetVisibility(visibility);
            _animator.gameObject.SetActive(visibility > 0);
        }

        protected override void Update() {
            base.Update();
            if (_coolDownTime > 0) {
                _coolDownTime -= Time.deltaTime;
            }
        }
    }
}
