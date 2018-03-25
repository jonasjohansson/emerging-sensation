using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class InputManager : MonoBehaviour {
	public OSC osc;
	[SerializeField] private FloatInput _floatInput;

	private float _value;

	// Use this for initialization
	void Start () {
		osc.SetAddressHandler("/CubeX", OnReceiveX);
	}

	void OnReceiveX(OscMessage message) {
		float newValue = message.GetFloat(0);
		_floatInput.SetNewValue(newValue);
	}

}
