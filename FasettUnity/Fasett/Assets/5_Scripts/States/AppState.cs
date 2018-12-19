using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public abstract class AppState : MonoBehaviour {
        protected StateManager _stateManager;

        public void Setup(StateManager stateManager) {
            _stateManager = stateManager;
        }

        public abstract void SetActive(bool active);
    }
}
