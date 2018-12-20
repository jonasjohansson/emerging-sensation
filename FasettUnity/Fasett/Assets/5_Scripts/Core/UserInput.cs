using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Input;
using UnityEngine.Windows.Speech;
using System;

namespace Fasett {
    public class UserInput : MonoBehaviour {
        private GestureRecognizer recognizer;
        private KeywordRecognizer _keywordRecognizer;

        public static Action OnUserSaidNextEffect;
        public static Action OnUserSaidCalibrateAllEffects;
        public static Action OnUserSaidDemoMode;
        public static Action OnUserSaidWireframe;
        public static Action OnUserSaidOK;

        private const string NEXT_EFFECT_PHRASE = "next";
        private const string CALIBRATE_ALL_EFFECTS_PHRASE = "calibrate all effects";
        private const string DEMO_MODE_PHRASE = "start demo";
        private const string SHOW_WIREFRAME_PHRASE = "wireframe";
        private const string OK_PHRASE = "ok";

        public void Setup(Core core) {
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
                if (OnUserSaidNextEffect != null) {
                    OnUserSaidNextEffect();
                }
            }
            else if(eventArgs.text == CALIBRATE_ALL_EFFECTS_PHRASE) {
                if (OnUserSaidCalibrateAllEffects != null) {
                    OnUserSaidCalibrateAllEffects();
                }
            }
            else if(eventArgs.text == DEMO_MODE_PHRASE) {
                if (OnUserSaidDemoMode != null) {
                    OnUserSaidDemoMode();
                }
            }
            else if(eventArgs.text == SHOW_WIREFRAME_PHRASE) {
                if (OnUserSaidWireframe != null) {
                    OnUserSaidWireframe();
                }
            }
            else if(eventArgs.text == OK_PHRASE) {
                if(OnUserSaidOK != null) {
                    OnUserSaidOK();
                }
            }
        }
    }
}
