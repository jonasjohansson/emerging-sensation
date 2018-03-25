using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LookAtInput : MonoBehaviour {
    [SerializeField] InputManager _inputManager;
    [SerializeField] float _treshold = .9f;

    private Camera _mainCamera;
    private bool _isLookingAt;

	private void Awake(){
        _mainCamera = Camera.main;
	}

	private void Update(){
        Vector3 dirFromAtoB = (transform.position - _mainCamera.transform.position).normalized;
        float dotProd = Vector3.Dot(dirFromAtoB, _mainCamera.transform.forward);

        SetLookingAt(dotProd > _treshold);
	}

    private void SetLookingAt(bool isLookingAt){
        if (isLookingAt != _isLookingAt){
            _isLookingAt = isLookingAt;
            _inputManager.TestSetFloat(isLookingAt ? 1 : 0);
        }
    }
}
