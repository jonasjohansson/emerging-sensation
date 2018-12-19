using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class Core : MonoBehaviour {
        public static Core Instance { get; private set; }
        [SerializeField] private UserInput _userInput;
        [SerializeField] private EffectManager _effectManager;
        [SerializeField] private NetworkHandler _networkHandler;
        [SerializeField] private StateManager _stateManager;
        [SerializeField] private SpatialMappingToggle _spatialMappingToggle;
        [SerializeField] private GameObject _fitCalibrationObject;
        [SerializeField] private GameObject _vignette;

        public EffectManager EffectManager { get { return _effectManager; } }
        public NetworkHandler NetworkHandler { get { return _networkHandler; } }

        private AppState _appState;
        private bool _calibratingHoloLensFit;

        protected void Start () {
            Instance = this;
            _effectManager.Setup();
            _networkHandler.Setup(this);
            _stateManager.Setup(this);
            _userInput.Setup(this);
            _spatialMappingToggle.Setup();
            _stateManager.SetState<SettingUpExhibition>();
            SetUpUserForDemo();
	    }

        public void SetUpUserForDemo() {
            _stateManager.SetState<SettingUpUserForDemo>();
            // Hide UI to return hololens to crew
            CalibrateHoloLensFit();
        }

        private void StartDemo() {
            _stateManager.SetState<DemoInProgress>();
        }

        public void StopDemo() {
            _stateManager.SetState<DemoEnded>();
            // Hide all effects
            // Show UI to return HoloLens to crew
        }

        public void CalibrateHoloLensFit() {
            if (!_calibratingHoloLensFit) {
                _calibratingHoloLensFit = true;
                _fitCalibrationObject.SetActive(true);
                _vignette.SetActive(false);
                UserInput.OnUserSaidOK += FitCalibrationCompleted;
            }
        }

        private void FitCalibrationCompleted() {
            if (_calibratingHoloLensFit) {
                _calibratingHoloLensFit = false;
                _fitCalibrationObject.SetActive(false);
                _vignette.SetActive(true);
                UserInput.OnUserSaidOK -= FitCalibrationCompleted;
                StartDemo();
            }
        }

        public void CalibrateAllEffects() {
            _effectManager.CalibrateAllEffects();
        }

        public void CalibrateNextEffect() {
            _effectManager.CalibrateNextEffect();
        }

        public void ToggleSpaceWireframe() {
            _spatialMappingToggle.ToggleRendering();
        }
    }
}
