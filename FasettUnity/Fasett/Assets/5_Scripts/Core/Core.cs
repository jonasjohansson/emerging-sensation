using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;

namespace Fasett {
    public class Core : MonoBehaviour {
        [SerializeField] private UserInput _userInput;
        [SerializeField] private EffectManager _effectManager;
        [SerializeField] private SpatialMappingToggle _spatialMappingToggle;

        private BroadcastReceiver receiver = new BroadcastReceiver();
        private string _oldMessage;
        private string _message;

        protected void Start () {
            _effectManager.Setup();
            _userInput.Setup(this);
            _spatialMappingToggle.Setup();
		    receiver.Receive(7003);
		    receiver.MessageReceived += ReceiveMessage;
	    }

        protected void OnDisable() {
            receiver.Dispose();
        }

        protected void Update() {
            if (_message != _oldMessage) {
                Debug.Log(_message);
                _oldMessage = _message;
            }
        }

        private void ReceiveMessage(string message, IPEndPoint remoteEndpoint) {
            string[] splitMessage = message.Split(' ');
            if(splitMessage.Length == 2) {
                string effectName = splitMessage[0];
                float value = 0;
                if(float.TryParse(splitMessage[1], out value)) {
                    _effectManager.SetEffectValueAsync(effectName, value);
                }
            }
            _message = message;
        }

        public void DebugReceiveMessage(string message) {
            ReceiveMessage(message, null);
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
