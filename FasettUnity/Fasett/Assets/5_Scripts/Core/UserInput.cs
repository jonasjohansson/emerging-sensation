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
        public static Action OnUserSaidCalibrateClosestEffect;
        public static Action OnUserSaidExhibitionSetup;
        public static Action OnUserSaidDemoMode;
        public static Action OnUserSaidWireframe;
        public static Action OnUserSaidOK;
        public static Action OnUserSaidInformation;

        private const string NEXT_EFFECT_PHRASE = "next effect";
        private const string CALIBRATE_ALL_EFFECTS_PHRASE = "calibrate all";
        private const string CALIBRATE_CLOSEST_EFFECT_PHRASE = "calibrate closest";
        private const string EXHIBITION_SETUP_PHRASE = "setup exhibition";
        private const string DEMO_MODE_PHRASE = "start demo";
        private const string SHOW_WIREFRAME_PHRASE = "wireframe";
        private const string OK_PHRASE = "ok";
        private const string INFORMATION_PHRASE = "information";

        public void Setup(Core core) {
            recognizer = new GestureRecognizer();
            recognizer.Tapped += UserTapped;
            recognizer.StartCapturingGestures();

            _keywordRecognizer = new KeywordRecognizer(new string[] { NEXT_EFFECT_PHRASE, CALIBRATE_ALL_EFFECTS_PHRASE, CALIBRATE_CLOSEST_EFFECT_PHRASE, EXHIBITION_SETUP_PHRASE, DEMO_MODE_PHRASE, SHOW_WIREFRAME_PHRASE, OK_PHRASE, INFORMATION_PHRASE });
            _keywordRecognizer.OnPhraseRecognized += PhraseRecognized;
            _keywordRecognizer.Start();
        }

        private void UserTapped(TappedEventArgs eventArgs) {
        }

        private void PhraseRecognized(PhraseRecognizedEventArgs eventArgs) {
            Action action = null;
            switch(eventArgs.text) {
                case NEXT_EFFECT_PHRASE:
                    action = OnUserSaidNextEffect;
                    break;
                case CALIBRATE_ALL_EFFECTS_PHRASE:
                    action = OnUserSaidCalibrateAllEffects;
                    break;
                case CALIBRATE_CLOSEST_EFFECT_PHRASE:
                    action = OnUserSaidCalibrateClosestEffect;
                    break;
                case EXHIBITION_SETUP_PHRASE:
                    action = OnUserSaidExhibitionSetup;
                    break;
                case DEMO_MODE_PHRASE:
                    action = OnUserSaidDemoMode;
                    break;
                case SHOW_WIREFRAME_PHRASE:
                    action = OnUserSaidWireframe;
                    break;
                case OK_PHRASE:
                    action = OnUserSaidOK;
                    break;
                case INFORMATION_PHRASE:
                    action = OnUserSaidInformation;
                    break;
            }
            if (action != null) {
                action();
            }
        }
    }
}
