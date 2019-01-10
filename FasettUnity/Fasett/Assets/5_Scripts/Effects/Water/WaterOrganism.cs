using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaterOrganism : MonoBehaviour {
    [SerializeField] private float _cooldownTime;
    [SerializeField] private float _attractionSpeed;

    [SerializeField] private float _freeRadius;
    [SerializeField] private float _focusRadius;
    [SerializeField] private float _movementDurationMin;
    [SerializeField] private float _movementDurationMax;
    [SerializeField] private AnimationCurve _movementCurve;
    [SerializeField] private float _maxDistanceFromCenter;

    private WaterEffect[] _triggers;
    private float _cooldown;
    private float _attraction;
    private WaterEffect _currentTrigger;
    private Vector3 _centerpoint;

    public void Setup(WaterEffect[] triggers) {
        _triggers = triggers;
        foreach (var trigger in _triggers) {
            trigger.OnPressedChanged += TouchChanged;
        }
    }

    public void SetCenterpoint(Vector3 centerpoint) {
        _centerpoint = centerpoint;
    }

    void OnEnable () {
        StartCoroutine(RandomMovement());
	}

    public void End() {
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

    private void TouchChanged(WaterEffect trigger) {
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
        float duration = UnityEngine.Random.Range(_movementDurationMin, _movementDurationMax);
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
        if (Vector3.Distance(transform.position, _centerpoint) > _maxDistanceFromCenter) {
            return _centerpoint + Random.insideUnitSphere * _freeRadius;
        }

        if(_currentTrigger == null) {
            return transform.position + Random.insideUnitSphere * _freeRadius;
        }
        return _currentTrigger.transform.position + Random.insideUnitSphere * _focusRadius;
    }

    private void OnDrawGizmosSelected() {
        Vector3 point = _centerpoint != Vector3.zero ? _centerpoint : transform.position;
        Gizmos.color = Color.cyan;
        Gizmos.DrawWireSphere(point, _maxDistanceFromCenter);
    }
}
