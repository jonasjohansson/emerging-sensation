using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class ToggleGameObject : Effect {
        [SerializeField] private GameObject _toggleObject;
        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);
            if(value >= 0.5f) {
                _toggleObject.SetActive(true);
            }
            else {
                _toggleObject.SetActive(false);
            }
        }
    }
}
