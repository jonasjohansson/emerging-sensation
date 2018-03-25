using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TestSlider : MonoBehaviour {
	[SerializeField] private Slider _slider;
    [SerializeField] private InputManager _inputManager;

	private void Start () {
        _slider.onValueChanged.AddListener(_inputManager.TestSetFloat);	
	}
}
