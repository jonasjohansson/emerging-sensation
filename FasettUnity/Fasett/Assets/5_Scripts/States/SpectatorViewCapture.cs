using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class SpectatorViewCapture : AppState {
        [SerializeField] private GameObject _ui;

        public override void SetActive(bool active) {
            if (active) {
                _ui.SetActive(false);
            }
            else {
                _ui.SetActive(true);
            }
        }
    }
}
