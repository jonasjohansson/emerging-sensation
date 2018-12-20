using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class SettingUpUserForDemo : AppState {
        [SerializeField] private GameObject _fitCalibrationObject;
        [SerializeField] private GameObject _vignette;

        public override void SetActive(bool active) {
            if (active) {
                _fitCalibrationObject.SetActive(true);
                _vignette.SetActive(false);
                UserInput.OnUserSaidOK += SetupCompleted;
            }
            else {
                _fitCalibrationObject.SetActive(false);
                _vignette.SetActive(true);
                UserInput.OnUserSaidOK -= SetupCompleted;
            }
        }

        private void SetupCompleted() {
            _stateManager.SetState<DemoInProgress>();
        }
    }
}
