using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class DebugEffect : Effect {
        [SerializeField] private TextMesh _valueText;

        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);
            _valueText.text = value.ToString();
        }
    }
}