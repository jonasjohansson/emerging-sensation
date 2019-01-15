using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class EffectTester : MonoBehaviour {
        [SerializeField] private Effect _effect;
        [SerializeField] private Color _color;
        [SerializeField, Range(0, 1)] private float _value;

        private void Update() {
            if (_effect) {
                _effect.SetColorAsync(_color);

                bool isSKyEffect = (_effect.GetType() == typeof(SkyEffect));
                bool isBodyEffect = (_effect.GetType() == typeof(SplittingCell));

                if (isSKyEffect) { 
                    _effect.SetValueAsync(_value * 255);
                } else if (isBodyEffect) { 
                    _effect.SetValueAsync(_value * 4);
                }
                else {
                    _effect.SetValueAsync(_value);
                }

            }
        }

    }
}