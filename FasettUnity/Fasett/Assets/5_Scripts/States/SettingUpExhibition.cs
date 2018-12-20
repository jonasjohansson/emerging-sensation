using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class SettingUpExhibition : AppState {
        [SerializeField] private EffectManager _effectManager;
        [SerializeField] private SpatialMappingToggle _spatialMappingToggle;
        [SerializeField] private GameObject _setupInstructions;

        public override void SetActive(bool active) {
            if (active) {
                UserInput.OnUserSaidCalibrateAllEffects += CalibrateAllEffects;
                UserInput.OnUserSaidNextEffect += CalibrateNextEffect;
                UserInput.OnUserSaidWireframe += ToggleSpaceWireframe;
                _setupInstructions.SetActive(true);
            }
            else {
                UserInput.OnUserSaidCalibrateAllEffects -= CalibrateAllEffects;
                UserInput.OnUserSaidNextEffect -= CalibrateNextEffect;
                UserInput.OnUserSaidWireframe -= ToggleSpaceWireframe;
                _setupInstructions.SetActive(false);
            }
        }

        private void CalibrateAllEffects() {
            _effectManager.CalibrateAllEffects();
        }

        private void CalibrateNextEffect() {
            _effectManager.CalibrateNextEffect();
        }

        private void ToggleSpaceWireframe() {
            _spatialMappingToggle.ToggleRendering();
        }
    }
}
