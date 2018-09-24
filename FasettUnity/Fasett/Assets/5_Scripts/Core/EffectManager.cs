using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class EffectManager : MonoBehaviour {
        [SerializeField] private Effect[] _effects;

        public void SetEffectValue(string effectName, float value) {
            foreach (Effect e in _effects) {
                if (e.Name == effectName) {
                    e.SetValue(value);
                }
            }
        }
    }
}
