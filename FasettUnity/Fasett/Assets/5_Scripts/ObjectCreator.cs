using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectCreator : MonoBehaviour {
    [SerializeField] private GameObject _prefab;
    [SerializeField] private float _radius;

    private GameObject _createdObject;

    [ContextMenu("Test")]
    public void Create() {
        if (_createdObject) {
            Destroy(_createdObject);
        }
        _createdObject = Instantiate(_prefab);
        _createdObject.transform.position = Random.insideUnitSphere * _radius;
        _createdObject.transform.localScale = _prefab.transform.localScale;
        Color randomColor = new Color(Random.value, Random.value, Random.value);
        _createdObject.GetComponent<MeshRenderer>().material.color = randomColor;
    }
}
