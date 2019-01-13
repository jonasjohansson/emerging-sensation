using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class DistanceFade : MonoBehaviour {
    [SerializeField] private Renderer _target;

    [SerializeField] private float _startBlend;
    [SerializeField] private float _endBlend;

    [SerializeField] private bool _debugTesting;

    private float _visibility;
    private Material _material;
    private float _lastSentVisibility = -1;
    public Action<float> OnVisibilityChanged;

    public static bool ShouldBeActive;

    private void Awake() {
        _material = _target.material;
    }

    void Update() {
        if (ShouldBeActive || _debugTesting) { 
            Vector3 cameraPosition = Camera.main.transform.position;
            float distance = Vector3.Distance(transform.position, cameraPosition);
            _visibility = Mathf.InverseLerp(_startBlend, _endBlend, distance);
        }
        else {
            _visibility = 0;
        }

        UpdateAmount();
    }

    private void UpdateAmount(){
        _material.SetFloat("_Fade", _visibility);
        _target.gameObject.SetActive(_visibility > 0);

        if (OnVisibilityChanged != null) {
            if (_lastSentVisibility != _visibility) {
                OnVisibilityChanged(1 - _visibility); //Visibility is the amount of the blocker, We want to send the inverse visibility to the effects.
                _lastSentVisibility = _visibility;
            }
        }
    }

    private void OnDrawGizmosSelected() {
        Gizmos.color = Color.blue * .5f;
        Gizmos.DrawWireSphere(transform.position, _startBlend);
        Gizmos.color = Color.blue * .8f;
        Gizmos.DrawWireSphere(transform.position, _endBlend);
    }
}
