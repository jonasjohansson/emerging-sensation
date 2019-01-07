using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaterOrganism : MonoBehaviour {
    [SerializeField] private List<WaterTrigger> _triggers;
    [SerializeField] private float _cooldownTime;
    [SerializeField] private float _attractionSpeed;

    [SerializeField] private float _freeRadius;
    [SerializeField] private float _focusRadius;
    [SerializeField] private float _movementDurationMin;
    [SerializeField] private float _movementDurationMax;
    [SerializeField] private AnimationCurve _movementCurve;
    [SerializeField] private float _maxDistanceFromCenter;

    private float _cooldown;
    private float _attraction;
    private WaterTrigger _currentTrigger;
    private Vector3 _centerpoint;

    // Use this for initialization
    void OnEnable () {
        foreach(var trigger in _triggers) {
            trigger.OnPressedChanged += TouchChanged;
        }
        _centerpoint = GetCenterPoint();
        StartCoroutine(RandomMovement());
	}

    private void OnDisable() {
        foreach(var trigger in _triggers) {
            trigger.OnPressedChanged -= TouchChanged;
        }
    }

    private void Update() {
        if(_currentTrigger) {
            if(_cooldown > 0) {
                _cooldown -= Time.deltaTime;
                if(_cooldown <= 0) {
                    _currentTrigger = null;
                }
            }
            _attraction = Mathf.Clamp01(_attraction - Time.deltaTime);
        }
    }

    private void TouchChanged(WaterTrigger trigger) {
        if (trigger != _currentTrigger && trigger.PressAmount > _attraction && _cooldown <= 0) {
            _currentTrigger = trigger;
            _cooldown = _cooldownTime;
        }

        if(trigger == _currentTrigger) {
            _attraction = Mathf.Clamp01(_attraction + Time.deltaTime / _attractionSpeed);
        }
    }

    private IEnumerator RandomMovement() {
        while(true) {
            yield return StartCoroutine(MoveTowardsTarget());
        }
    }

    private IEnumerator MoveTowardsTarget() {
        float duration = UnityEngine.Random.RandomRange(_movementDurationMin, _movementDurationMax);
        Vector3 startPos = transform.position;
        Vector3 endPos = SetNewPosition();

        float time = 0;
        while(time < 1) {
            time = Mathf.Clamp01(time + Time.deltaTime / duration);
            transform.position = Vector3.Lerp(startPos, endPos, _movementCurve.Evaluate(time));            
            yield return 0;
        }
    }

    private Vector3 SetNewPosition() {
        if(Vector3.Distance(transform.position, _centerpoint) > _maxDistanceFromCenter) {
            return _centerpoint + Random.insideUnitSphere * _freeRadius;
        }

        if(_currentTrigger == null) {
            return transform.position + Random.insideUnitSphere * _freeRadius;
        }
        return _currentTrigger.transform.position + Random.insideUnitSphere * _focusRadius;
    }


    private Vector3 GetCenterPoint() {
        Vector3 sum = Vector3.zero;
        if(_triggers == null || _triggers.Count == 0) {
            return sum;
        }

        foreach(var trigger in _triggers) {
            sum += trigger.transform.position;
        }
        return sum / _triggers.Count;
    }

    private void OnDrawGizmosSelected() {
        if(_centerpoint != Vector3.zero) {
            Gizmos.color = Color.cyan;
            Gizmos.DrawWireSphere(_centerpoint, _maxDistanceFromCenter);
        }
    }
}
