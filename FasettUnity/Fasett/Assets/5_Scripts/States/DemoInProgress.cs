using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class DemoInProgress : AppState {
        private float _demoDuration = 900; // 15 minutes
        private float _demoCounter;
        private bool _running;

        protected void Update() {
            if (_running) {
                _demoCounter -= Time.deltaTime;
                if(_demoCounter <= 0.0f) {
                    Core.Instance.StopDemo();
                }
            }
        }

        public override void SetActive(bool active) {
            _demoCounter = _demoDuration;
            _running = active;
            // Show all effects
        }
    }
}
