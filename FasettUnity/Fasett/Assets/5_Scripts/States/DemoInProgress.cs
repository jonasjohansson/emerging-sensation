using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class DemoInProgress : AppState {
        [SerializeField] private EffectManager _effectManager;
        private float _demoDuration = 600; // 15 minutes
        private float _demoCounter;
        private bool _running;

        protected void Update() {
            if (_running) {
                _demoCounter -= Time.deltaTime;
                if(_demoCounter <= 0.0f) {
                    _stateManager.SetState<DemoEnded>();
                }
            }
        }

        public override void SetActive(bool active) {
            DistanceFade.ShouldBeActive = active;
            if (active) {
                _demoCounter = _demoDuration;
                _running = true;
                UserInput.OnUserSaidDemoMode += SetUpUserForDemo;
                _effectManager.ShowEffects();
            }
            else {
                _running = false;
                UserInput.OnUserSaidDemoMode -= SetUpUserForDemo;
            }
        }

        private void SetUpUserForDemo() {
            _stateManager.SetState<SettingUpUserForDemo>();
        }
    }
}
