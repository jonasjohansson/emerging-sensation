using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class SettingUpExhibition : AppState {
        [SerializeField] private EffectManager _effectManager;
        [SerializeField] private GameObject _setupInstructions;

        public override void SetActive(bool active) {
            if (active) {
                UserInput.OnUserSaidCalibrateAllEffects += CalibrateAllEffects;
                UserInput.OnUserSaidCalibrateClosestEffect += CalibrateClosestEffect;
                UserInput.OnUserSaidNextEffect += CalibrateNextEffect;
                UserInput.OnUserSaidOK += CalibrateNextEffect;
                UserInput.OnUserSaidInformation += ToggleInformation;
                UserInput.OnUserSaidDemoMode += SetUpUserForDemo;
                _setupInstructions.SetActive(true);
            }
            else {
                UserInput.OnUserSaidCalibrateAllEffects -= CalibrateAllEffects;
                UserInput.OnUserSaidCalibrateClosestEffect -= CalibrateClosestEffect;
                UserInput.OnUserSaidNextEffect -= CalibrateNextEffect;
                UserInput.OnUserSaidOK -= CalibrateNextEffect;
                UserInput.OnUserSaidInformation -= ToggleInformation;
                UserInput.OnUserSaidDemoMode -= SetUpUserForDemo;
                _setupInstructions.SetActive(false);
            }
        }

        private void CalibrateAllEffects() {
            _effectManager.CalibrateAllEffects();
        }

        private void CalibrateClosestEffect() {
            _effectManager.CalibrateClosestEffect();
        }

        private void CalibrateNextEffect() {
            _effectManager.CalibrateNextEffect();
        }

        private void ToggleInformation() {
            _setupInstructions.SetActive(!_setupInstructions.activeSelf);
        }

        private void SetUpUserForDemo() {
            if (!_effectManager.IsCalibrating) {
                _stateManager.SetState<SettingUpUserForDemo>();
            }
        }
    }
}
