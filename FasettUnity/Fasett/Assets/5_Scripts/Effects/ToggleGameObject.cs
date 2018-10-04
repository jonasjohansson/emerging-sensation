using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class ToggleGameObject : Effect {
        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);
            if(value >= 0.5f) {
                gameObject.SetActive(true);
            }
            else {
                gameObject.SetActive(false);
            }
        }
    }
}
