using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett { 
    public class SplittingCell : Effect {
        [SerializeField] private Animator _animator;
        [SerializeField] private float _coolDown = 1;

        [SerializeField] private RandomSound _splitSound;
        [SerializeField] private AudioSource _combineSound;
        private int _splitCount = 0;

        private float _coolDownTime;

        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);

            if (value >= 0.5f && _coolDownTime <= 0) {
                _splitCount = (_splitCount + 1) % 4;
                if (_splitCount == 0) {
                    _combineSound.Play();
                }
                else {
                    _splitSound.Play();
                }
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
