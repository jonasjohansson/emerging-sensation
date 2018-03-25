using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public class Main : MonoBehaviour {

    public InputManager inputManager;
    public BroadcastReceiver receiver = new BroadcastReceiver ();
	// Use this for initialization
	void Start () {
		receiver.Receive (7003);
		receiver.MessageReceived += Log;
	}

    private void OnDisable()
    {
        receiver.Dispose();
    }

    // Update is called once per frame
    void Log (string message) {
		Debug.Log (message);
        float value = float.Parse(message);
        inputManager.CreateObject();  
    }
}
