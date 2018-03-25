using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public class Main : MonoBehaviour {

	public BroadcastReceiver receiver = new BroadcastReceiver ();
	// Use this for initialization
	void Start () {
		receiver.Receive (7003);
		receiver.MessageReceived += Log;
	}
	
	// Update is called once per frame
	void Log (string message, IPEndPoint remoteEndpoint) {
		Debug.Log (message);
	}
}
