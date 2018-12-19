using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class StateManager : MonoBehaviour {
        [SerializeField] private AppState[] _states;

        public void Setup(Core core) {
        }

        public void SetState<T>() where T : AppState {
            foreach (AppState appState in _states) {
                appState.SetActive(appState is T);
            }
        }
    }
}
