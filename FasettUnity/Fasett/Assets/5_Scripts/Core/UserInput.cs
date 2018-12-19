using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Input;
using UnityEngine.Windows.Speech;
using System;

namespace Fasett {
    public class UserInput : MonoBehaviour {
        private Core _core;
        private GestureRecognizer recognizer;
        private KeywordRecognizer _keywordRecognizer;

        public static Action OnUserSaidOK;

        private const string NEXT_EFFECT_PHRASE = "next";
        private const string CALIBRATE_ALL_EFFECTS_PHRASE = "calibrate all effects";
        private const string DEMO_MODE_PHRASE = "start demo";
        private const string SHOW_WIREFRAME_PHRASE = "wireframe";
        private const string OK_PHRASE = "ok";

        public void Setup(Core core) {
            _core = core;

            recognizer = new GestureRecognizer();
            recognizer.Tapped += UserTapped;
            recognizer.StartCapturingGestures();

            _keywordRecognizer = new KeywordRecognizer(new string[] { NEXT_EFFECT_PHRASE, CALIBRATE_ALL_EFFECTS_PHRASE, DEMO_MODE_PHRASE, SHOW_WIREFRAME_PHRASE, OK_PHRASE });
            _keywordRecognizer.OnPhraseRecognized += PhraseRecognized;
            _keywordRecognizer.Start();
        }

        private void UserTapped(TappedEventArgs eventArgs) {
            
        }

        private void PhraseRecognized(PhraseRecognizedEventArgs eventArgs) {
            if(eventArgs.text == NEXT_EFFECT_PHRASE) {
                _core.CalibrateNextEffect();
            }
            else if(eventArgs.text == CALIBRATE_ALL_EFFECTS_PHRASE) {
                _core.CalibrateAllEffects();
            }
            else if(eventArgs.text == DEMO_MODE_PHRASE) {
                _core.SetUpUserForDemo();
            }
            else if(eventArgs.text == SHOW_WIREFRAME_PHRASE) {
                _core.ToggleSpaceWireframe();
            }
            else if(eventArgs.text == OK_PHRASE) {
                if(OnUserSaidOK != null) {
                    OnUserSaidOK();
                }
            }
        }
    }
}
