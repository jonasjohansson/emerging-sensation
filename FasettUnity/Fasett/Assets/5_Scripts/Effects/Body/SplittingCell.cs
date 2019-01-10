using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett { 
    public class SplittingCell : Effect {
        [SerializeField] private Animator _animator;

        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);
            if (value >= 0.5f) {
                _animator.SetTrigger("Activate");
            }
        }
    }
}
