using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Fasett {
    public class TestSlider : MonoBehaviour {
        [SerializeField] private string _nodeName;
	    [SerializeField] private Slider _slider;
        [SerializeField] private Core _core;

	    private void Start () {
            _slider.onValueChanged.AddListener(SetFloat);	
	    }

        private void SetFloat(float value) {
            _core.DebugReceiveMessage(string.Format("{0}/{1}", _nodeName, value));
        }
    }
}
