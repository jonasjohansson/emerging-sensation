using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Input;

namespace Fasett {
    public class UserInput : MonoBehaviour {
        private GestureRecognizer recognizer;

        [SerializeField] private SpatialMappingToggle _spatialMappingToggle;

        public void Setup() {
            recognizer = new GestureRecognizer();
            recognizer.Tapped += UserTapped;
            recognizer.StartCapturingGestures();
        }

        private void UserTapped(TappedEventArgs eventArgs) {
            _spatialMappingToggle.ToggleRendering();
        }
    }
}
