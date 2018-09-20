using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class FloatInput : MonoBehaviour {
	public float Value { private set; get; }
	public Action<float> OnNewValue;

	[SerializeField] private float _changeTime;
	[SerializeField] private AnimationCurve _changeCurve;

	public void SetNewValue(float value, bool force = false) {
		if (Value != value || force){
			StopAllCoroutines();
			StartCoroutine(Change(value));
		}
	}

	private IEnumerator Change(float value) {
		if (_changeTime <= 0) {
			UpdateValue(value);
		}
		else{
			float time = 0;
			float fromValue = Value;
			while (time < 1){
				time = Mathf.Clamp01(time + Time.deltaTime / _changeTime);
				UpdateValue(Mathf.Lerp(fromValue, value, _changeCurve.Evaluate(time)));
				yield return 0;
			}
		}
	}

	private void UpdateValue(float value) {
		Value = value;
		if (OnNewValue != null){
			OnNewValue(Value);
		}
	}
}
