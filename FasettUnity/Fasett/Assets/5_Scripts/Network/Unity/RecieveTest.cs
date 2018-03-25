using UnityEngine;
using System.Collections;

public class RecieveTest : MonoBehaviour {
    #if UNITY_EDITOR

   	public OSC osc;
    public InputManager inputManager;

	// Use this for initialization
	void Start () {
       osc.SetAddressHandler("/d0", OnReceive0);
    }

    void OnReceive0(OscMessage message) {
		float val = message.GetInt(0);
        inputManager.TestSetFloat(val);
    }
    #endif
}
