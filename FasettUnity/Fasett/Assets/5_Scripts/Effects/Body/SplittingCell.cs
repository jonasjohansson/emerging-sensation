using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SplittingCell : MonoBehaviour {
    [SerializeField] private KeyCode _key;

    private Animator _animator;

	// Use this for initialization
	void Start () {
        _animator = GetComponent<Animator>();
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown(_key)) {
            _animator.SetTrigger("Activate");
        }
    }
}
