using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class Core : MonoBehaviour {
        private BroadcastReceiver receiver = new BroadcastReceiver ();
        [SerializeField] private EffectManager _effectManager;

        protected void Start () {
		    receiver.Receive(7003);
		    receiver.MessageReceived += ReceiveMessage;
	    }

        protected void OnDisable() {
            receiver.Dispose();
        }

        private void ReceiveMessage (string message) {
            string[] splitMessage = message.Split('/');
            if (splitMessage.Length == 2) {
                string node = splitMessage[0];
                float value = float.Parse(splitMessage[1]);
                _effectManager.SetEffectValue(node, value);
            }
        }

        public void DebugReceiveMessage(string message) {
            ReceiveMessage(message);
        }
    }
}
