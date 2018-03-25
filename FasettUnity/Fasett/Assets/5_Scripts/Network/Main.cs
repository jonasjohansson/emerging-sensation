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

    private string _message;
    private string _oldMessage;
	// Use this for initialization
	void Start () {
		receiver.Receive (7003);
		receiver.MessageReceived += Log;
	}

    private void OnDisable()
    {
        receiver.Dispose();
    }

    void Log (string message) {
        _message = message;
		Debug.Log (message);
    }

	private void Update()
	{
        if (_message != _oldMessage){
            _oldMessage = _message;
            float value = float.Parse(_message);
            inputManager.TestSetFloat(Mathf.InverseLerp(0, 127, value));
            inputManager.CreateObject(); 
        }
	}
}
