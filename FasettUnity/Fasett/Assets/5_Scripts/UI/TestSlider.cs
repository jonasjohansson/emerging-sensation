using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TestSlider : MonoBehaviour {
	[SerializeField] private Slider _slider;
	[SerializeField] private FloatInput _floatInput;

	private void Start () {
		_slider.onValueChanged.AddListener((value) => _floatInput.SetNewValue(value));	
	}
}
