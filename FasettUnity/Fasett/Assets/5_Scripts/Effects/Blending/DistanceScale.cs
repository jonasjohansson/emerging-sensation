using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DistanceScale : MonoBehaviour {
    [SerializeField] private GameObject[] _disablers;

    [SerializeField] private Renderer _target;

    [SerializeField] private float _startBlend;
    [SerializeField] private float _endBlend;

    [SerializeField] public float Amount;

    private Material _material;

    public static bool ShouldBeActive;

    private void Awake() {
        _material = _target.material;
    }

    void Update() {
        if (ShouldBeActive) { 
            Vector3 cameraPosition = Camera.main.transform.position;
            float distance = Vector3.Distance(transform.position, cameraPosition);
            Amount = Mathf.InverseLerp(_startBlend, _endBlend, distance);
        }
        else {
            Amount = 0;
        }

        _material.SetFloat("_Fade", Amount);
        SetObjectsActive();
    }

    private void SetObjectsActive(){
        for (int i = 0; i< _disablers.Length; i++) {
            _disablers[i].SetActive(Amount != 1);
        }
        _target.gameObject.SetActive(Amount > 0);
    }

    private void OnDrawGizmosSelected() {
        Gizmos.color = Color.blue * .5f;
        Gizmos.DrawWireSphere(transform.position, _startBlend);
        Gizmos.color = Color.blue * .8f;
        Gizmos.DrawWireSphere(transform.position, _endBlend);
    }
}
