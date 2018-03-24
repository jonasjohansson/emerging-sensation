using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class FloatInput : MonoBehaviour {
	public float Value {private set; get;}
	public Action<float> OnNewValue;

	public void SetNewValue(float value, bool force = false){
		if (Value != value || force){
			Value = value;
			if (OnNewValue != null){
				OnNewValue(Value);
			}
		}
	}
}
