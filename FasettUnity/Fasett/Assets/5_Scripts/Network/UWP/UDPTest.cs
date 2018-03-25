using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

public class UDPTest : MonoBehaviour
{
    public InputManager inputManager;

#if UNITY_EDITOR
    // Use this for initialization
    void Start()
    {
        UDPCommunication.Instance.OnMessage += OnReceive;
    }

    void OnReceive(byte[] message)
    {
        string returnData = Encoding.ASCII.GetString(message);
        Debug.Log(returnData);
        //float val = returnData == "/d0/1";
        //inputManager.TestSetFloat(val);
    }
#endif
}
