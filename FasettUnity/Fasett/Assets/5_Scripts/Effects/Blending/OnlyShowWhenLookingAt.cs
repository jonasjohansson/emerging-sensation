using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OnlyShowWhenLookingAt : MonoBehaviour {
    [SerializeField] private GameObject _target;
    [Header("CameraInFrontOf")]
    [SerializeField, Range(-1,1)] private float _startBlend;
    [SerializeField, Range(-1, 1)] private float _endBlend;

    [SerializeField] public float InFrontOf;

    void Update () {
        Vector3 cameraPosition = Camera.main.transform.position;
        Vector3 viewDir =( transform.position - cameraPosition).normalized;
        float dot = Vector3.Dot(transform.forward, viewDir);
        InFrontOf = Mathf.InverseLerp(_endBlend, _startBlend, dot);

        _target.SetActive(InFrontOf > 0);
    }
}
