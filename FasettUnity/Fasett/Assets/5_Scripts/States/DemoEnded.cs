using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class DemoEnded : AppState {
        [SerializeField] private GameObject _demoEndedInstructions;
        [SerializeField] private EffectManager _effectManager;

        public override void SetActive(bool active) {
            if (active) {
                _demoEndedInstructions.SetActive(true);
                _effectManager.HideEffects();
            }
            else {
                _demoEndedInstructions.SetActive(false);
                _effectManager.ShowEffects();
            }
        }
    }
}
