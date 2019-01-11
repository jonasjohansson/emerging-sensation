using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Fasett;

public class SkyController : MonoBehaviour {
    [SerializeField] private Transform[] _centerObjects;
    [SerializeField] private Effect[] _effects;

    private void Awake() {
        _effects = GetComponentsInChildren<Effect>(false);
    }

    // Use this for initialization
    protected virtual void OnEnable () {
        StartCoroutine(CenterEverySeconds(3));
    }

    protected virtual void OnDisable() {
    }

    private IEnumerator CenterEverySeconds(int seconds) { 
        while (true) {
            Vector3 center = GetCenterPoint();
            foreach (Transform trans in _centerObjects) {
                trans.position = center;
            }
            yield return new WaitForSeconds(seconds);
        }
    }


    private Vector3 GetCenterPoint() {
        Vector3 sum = Vector3.zero;
        if(_effects == null || _effects.Length == 0) {
            return sum;
        }

        foreach(var trigger in _effects) {
            sum += trigger.transform.position;
        }
        return sum / _effects.Length;
    }

    [ContextMenu("Find in Children")]
    private void FindInChildren() {
        _effects = GetComponentsInChildren<Effect>(false);
    }
}
