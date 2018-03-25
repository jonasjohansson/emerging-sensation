#if !UNITY_EDITOR
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace FasettNet {
    public class UWPOsc : OSCWrapper
    {
        public override bool SocketsOpen() {
            Debug.Log("NotImplemented");
            return false;
        }
        public override bool Open(int localHost) { 
            Debug.Log("NotImplemented");
            return false;
        }
        public override void Close() { 
            Debug.Log("NotImplemented");
        }
        public override void SendPacket(byte[] packet, int length, string remoteHostName, int remotePort) {
            Debug.Log("NotImplemented");
        }
        public override byte[] Receive(int localPort) {
            Debug.Log("NotImplemented");
            return null;
        }
    }
}
#endif
