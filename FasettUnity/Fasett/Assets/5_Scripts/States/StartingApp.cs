using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class StartingApp : AppState {
        [SerializeField] private EffectManager _effectManager;
        [SerializeField] private TextMesh _startupMessage;

        private bool _exhibitionSetup;

        public override void SetActive(bool active) {
            if(active) {
                _startupMessage.gameObject.SetActive(true);
                _effectManager.Setup(EffectSetupCompleteCallback);
                UserInput.OnUserSaidExhibitionSetup += UserSaidExhibitionSetup;
            }
            else {
                _startupMessage.gameObject.SetActive(false);
                UserInput.OnUserSaidExhibitionSetup -= UserSaidExhibitionSetup;
            }
        }

        private void UserSaidExhibitionSetup() {
            _exhibitionSetup = true;
            _startupMessage.text = _startupMessage.text + "\nSetting up exhibition...";
        }

        private void EffectSetupCompleteCallback(bool successful, string message) {
            if (_exhibitionSetup) {
                _startupMessage.text = message + " Say 'OK' to continue to setup.";
                UserInput.OnUserSaidOK += ContinueToExhibitionSetup;
            }
            else {
                if (successful) {
                    _stateManager.SetState<SettingUpUserForDemo>();
                }
                else {
                    _startupMessage.text = "Couldn't load effects. Please give the HoloLens to exhibition staff.";
                }
            }
        }

        private void ContinueToExhibitionSetup() {
            UserInput.OnUserSaidOK -= ContinueToExhibitionSetup;
            _stateManager.SetState<SettingUpExhibition>();
        }
    }
}
