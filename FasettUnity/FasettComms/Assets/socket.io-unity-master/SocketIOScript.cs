using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Quobject.SocketIoClientDotNet.Client;
using Newtonsoft.Json;

public class ChatData {
	public string id;
	public string msg;
};

public class SocketIOScript : MonoBehaviour {
	public string serverURL = "http://localhost:3000";

	protected Socket socket = null;
	protected List<string> chatLog = new List<string> (); 

	void Destroy() {
		DoClose ();
	}

	// Use this for initialization
	void Start () {
		DoOpen ();
	}
	
	// Update is called once per frame
	void Update () {
	}

	void DoOpen() {
		if (socket == null) {
			socket = IO.Socket (serverURL);
			socket.On (Socket.EVENT_CONNECT, () => {
				lock(chatLog) {
					// Access to Unity UI is not allowed in a background thread, so let's put into a shared variable
					chatLog.Add("Socket.IO connected.");
				}
			});
			socket.On ("chat", (data) => {
				string str = data.ToString();
				Debug.Log(str);
			});
		}
	}

	void DoClose() {
		if (socket != null) {
			socket.Disconnect ();
			socket = null;
		}
	}
}
