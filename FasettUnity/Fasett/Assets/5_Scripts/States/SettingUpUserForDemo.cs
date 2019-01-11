using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class SettingUpUserForDemo : AppState {
        [SerializeField] private GameObject _fitCalibrationObject;

        public override void SetActive(bool active) {
            if (active) {
                _fitCalibrationObject.SetActive(true);
                UserInput.OnUserSaidOK += SetupCompleted;
            }
            else {
                _fitCalibrationObject.SetActive(false);
                UserInput.OnUserSaidOK -= SetupCompleted;
            }
        }

        private void SetupCompleted() {
            _stateManager.SetState<DemoInProgress>();
        }
    }
}
