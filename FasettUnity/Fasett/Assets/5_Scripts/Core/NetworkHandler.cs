using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;

namespace Fasett {
    public class NetworkHandler : MonoBehaviour {
        private Core _core;
        private BroadcastReceiver _receiver = new BroadcastReceiver();
        private string _oldMessage;
        private string _message;

        public void Setup(Core core) {
            _core = core;
            _receiver.Receive(7003);
            _receiver.MessageReceived += ReceiveMessage;
        }

        protected void Update() {
            if(_message != _oldMessage) {
                Debug.Log(_message);
                _oldMessage = _message;
            }
        }

        protected void OnDisable() {
            _receiver.Dispose();
        }

        private void ReceiveMessage(string message, IPEndPoint remoteEndpoint) {
            string[] splitMessage = message.Split(' ');
            if(splitMessage.Length == 2) {
                string effectName = splitMessage[0];
                float value = 0;
                if(float.TryParse(splitMessage[1], out value)) {
                    _core.EffectManager.SetEffectValueAsync(effectName, value);
                }
            }
            _message = message;
        }

        public void DebugReceiveMessage(string message) {
            ReceiveMessage(message, null);
        }
    }
}
