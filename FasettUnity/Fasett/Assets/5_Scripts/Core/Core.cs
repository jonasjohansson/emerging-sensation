using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;

namespace Fasett {
    public class Core : MonoBehaviour {
        private BroadcastReceiver receiver = new BroadcastReceiver ();
        [SerializeField] private EffectManager _effectManager;
        [SerializeField] private UserInput _userInput;
        private string _oldMessage;
        private string _message;

        protected void Start () {
            _effectManager.Setup();
            _userInput.Setup();
		    receiver.Receive(7003);
		    receiver.MessageReceived += ReceiveMessage;
	    }

        protected void OnDisable() {
            receiver.Dispose();
        }

        private void ReceiveMessage (string message, IPEndPoint remoteEndpoint) {
            _message = message;
        }

        protected void Update() {
            if (_message != _oldMessage) {
                Debug.Log(_message);
                string[] splitMessage = _message.Split(' ');
                if(splitMessage.Length == 2) {
                    string effectName = splitMessage[0];
                    float value = 0;
                    if (float.TryParse(splitMessage[1], out value)) {
                        _effectManager.SetEffectValue(effectName, value);
                    }
                }
                _oldMessage = _message;
            }
        }

        public void DebugReceiveMessage(string message) {
            ReceiveMessage(message, null);
        }
    }
}
