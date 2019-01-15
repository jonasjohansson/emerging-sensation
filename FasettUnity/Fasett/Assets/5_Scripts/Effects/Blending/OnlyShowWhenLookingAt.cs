using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett { 
    public class OnlyShowWhenLookingAt : MonoBehaviour {
        [SerializeField] private SkyEffect _skyeffect;
        [Header("CameraInFrontOf")]
        [SerializeField, Range(-1,1)] private float _startBlend;
        [SerializeField, Range(-1, 1)] private float _endBlend;

        [SerializeField] public float InFrontOf;

        void Update () {
            if (_skyeffect.IsVisible) { 
                Vector3 cameraPosition = Camera.main.transform.position;
                Vector3 viewDir = (transform.position - cameraPosition).normalized;
                float dot = Vector3.Dot(-transform.forward.normalized, viewDir);
                InFrontOf = Mathf.InverseLerp(_startBlend, _endBlend, dot);

                _skyeffect.SetSideView(InFrontOf);
            }
        }
    }
}
