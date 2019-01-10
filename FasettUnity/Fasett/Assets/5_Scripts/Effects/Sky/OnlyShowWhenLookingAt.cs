using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OnlyShowWhenLookingAt : MonoBehaviour {
    [SerializeField] private GameObject _target;
    [SerializeField, Range(-1,1)] private float _dot;

    void Update () {
        Vector3 cameraPosition = Camera.main.transform.position;
        Vector3 viewDir =( transform.position - cameraPosition).normalized;
        float dot = Vector3.Dot(transform.forward, viewDir);
        _target.SetActive(_dot > dot );
    }
}
