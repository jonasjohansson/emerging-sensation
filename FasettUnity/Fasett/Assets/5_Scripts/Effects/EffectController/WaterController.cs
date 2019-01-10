using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaterController : MonoBehaviour {
    [SerializeField] private WaterEffect[]_triggers;
    [SerializeField] private WaterOrganism[] _organisms;
    [SerializeField] private Transform[] _otherCenter;

    // Use this for initialization
    void OnEnable () {
        foreach (WaterOrganism organism in _organisms) {
            organism.Setup(_triggers);
        }

        StartCoroutine(CenterEverySeconds(3));
    }

    private void OnDisable() {
        foreach (WaterOrganism organism in _organisms) {
            organism.End();
        }
    }


    private IEnumerator CenterEverySeconds(int seconds) { 
        while (true) {
            Vector3 center = GetCenterPoint();
            foreach (Transform trans in _otherCenter) {
                trans.position = center;
            }
            foreach (WaterOrganism organism in _organisms) {
                organism.SetCenterpoint(center);
            }
            yield return new WaitForSeconds(seconds);
        }
    }

    private Vector3 GetCenterPoint() {
        Vector3 sum = Vector3.zero;
        if(_triggers == null || _triggers.Length == 0) {
            return sum;
        }

        foreach(var trigger in _triggers) {
            sum += trigger.transform.position;
        }
        return sum / _triggers.Length;
    }

    [ContextMenu("Find in Children")]
    private void FindInChildren() {
        _triggers = GetComponentsInChildren<WaterEffect>(true);
        _organisms = GetComponentsInChildren<WaterOrganism>(true);
    }
}
