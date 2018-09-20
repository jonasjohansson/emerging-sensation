using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LookAtInput : MonoBehaviour {
    [SerializeField] private float _threshold = .9f;

    private Camera _mainCamera;
    private bool _isLookingAt;

	protected void Awake() {
        _mainCamera = Camera.main;
	}

	protected void Update() {
        Vector3 dirFromAtoB = (transform.position - _mainCamera.transform.position).normalized;
        float dotProd = Vector3.Dot(dirFromAtoB, _mainCamera.transform.forward);

        SetLookingAt(dotProd > _threshold);
	}

    private void SetLookingAt(bool isLookingAt){
        if (isLookingAt != _isLookingAt){
            _isLookingAt = isLookingAt;
        }
    }
}
