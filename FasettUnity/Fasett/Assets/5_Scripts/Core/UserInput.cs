using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Input;
using UnityEngine.Windows.Speech;

namespace Fasett {
    public class UserInput : MonoBehaviour {
        private Core _core;

        private GestureRecognizer recognizer;
        private KeywordRecognizer _keywordRecognizer;

        public void Setup(Core core) {
            _core = core;

            recognizer = new GestureRecognizer();
            recognizer.Tapped += UserTapped;
            recognizer.StartCapturingGestures();

            _keywordRecognizer = new KeywordRecognizer(new string[] { "next", "calibrate all effects", "wireframe" });
            _keywordRecognizer.OnPhraseRecognized += PhraseRecognized;
            _keywordRecognizer.Start();
        }

        private void UserTapped(TappedEventArgs eventArgs) {
            
        }

        private void PhraseRecognized(PhraseRecognizedEventArgs eventArgs) {
            if(eventArgs.text == "next") {
                _core.CalibrateNextEffect();
            }
            else if(eventArgs.text == "calibrate all effects") {
                _core.CalibrateAllEffects();
            }
            else if(eventArgs.text == "wireframe") {
                _core.ToggleSpaceWireframe();
            }
        }
    }
}
