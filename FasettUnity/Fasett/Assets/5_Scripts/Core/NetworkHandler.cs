﻿using System.Collections;
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
            if (splitMessage.Length == 4) {
                string effectName = splitMessage[0];
                float r = 0;
                float g = 0;
                float b = 0;
                if (float.TryParse(splitMessage[1], out r) && float.TryParse(splitMessage[2], out g) && float.TryParse(splitMessage[3], out b)) {
                    Color color = new Color(r / 255, g / 255, b / 255);
                    _core.EffectManager.SetEffectColorAsync(effectName, color);
                }
            }
            _message = message;
        }

        public void DebugReceiveMessage(string message) {
            ReceiveMessage(message, null);
        }
    }
}
