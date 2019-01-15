using System;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett { 
    public class WaterEffectGroup : MonoBehaviour {
        private WaterEffect[] _waterEffects;

        private void Awake() {
            _waterEffects = GetComponentsInChildren<WaterEffect>();
            foreach (WaterEffect effect in _waterEffects) {
                effect.OnTriggered += NewEffectTriggred;
            }
        }

        private void NewEffectTriggred(WaterEffect obj) {
            obj.Activate();
        }
    }
}