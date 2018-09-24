using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class ToggleGameObject : Effect {
        public override void SetValue(float value) {
            if (value >= 0.5f) {
                gameObject.SetActive(true);
            }
            else {
                gameObject.SetActive(false);
            }
        }
    }
}
