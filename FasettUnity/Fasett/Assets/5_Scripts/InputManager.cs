using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class InputManager : MonoBehaviour {
	[SerializeField] private FloatInput _testFloatInput;

	private float _value;

    public void TestSetFloat(float value){
        _testFloatInput.SetNewValue(value);
    }
}
