using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA.Input;

namespace Fasett {
    public class TransformByHands : MonoBehaviour {
        private class Hand {
            public GameObject GameObject;
            public uint ID;
        }

        #region Variables
        private List<Hand> _trackedHands = new List<Hand>();

        // BINDINGS
        private Transform _playerEyes;
        private GameObject _transformer;

        // CURRENT STATE
        private bool _isTransforming;
        private List<Transform> _grabPoints = new List<Transform>();

        // Rotation locked state
        private bool _lockedRotating;
        private float _lockedRotationVelocity;
        private Quaternion _lockedRotationQuaternion;

        // Constraints
        private bool _allowMove = true;
        private bool _allowRotate = true;
        private bool _allowScale = false;
        private bool _allowSlide = false;

        // ROTATION
        private Quaternion _rotationalDifference;
        private float _startRotationalAngleVelocity;
        private float _rotationalAngleVelocity;
        private List<RotationalVelocityMeasurement> _rotationalVelocityMeasurements = new List<RotationalVelocityMeasurement>();
        private float _rotationalVelocityFadeTime = 2.5f;
        private float _rotationalVelocityFadeCounter;
        private Quaternion _oldRotation;

        // SCALING
        private float _scaleVelocity;
        private float _startScaleVelocity;
        private List<ScaleVelocityMeasurement> _scaleVelocityMeasurements = new List<ScaleVelocityMeasurement>();
        private float _scaleVelocityFadeTime = 1.5f;
        private float _scaleVelocityFadeCounter;
        private float _oldScale;
        [SerializeField] private float _minScale = 0.1f;
        private float AbsoluteMinScale { get { return _minScale * 0.1f; } }
        [SerializeField] private float _maxScale = 3.0f;
        private float AbsoluteMaxScale { get { return _maxScale * 1.5f; } }

        // SLIDING
        private Vector3 _movementVelocity;
        private float _movementVelocityMagnitude;
        private float _startMovementVelocityMagnitude;
        private List<MovementVelocityMeasurement> _movementVelocityMeasurements = new List<MovementVelocityMeasurement>();
        private float _movementVelocityFadeTime = 2.5f;
        private float _movementVelocityFadeCounter;
        private Vector3 _oldPosition;
        private Transform _transformerGhost;
        private float _doubleGrabReleaseTime;
        [SerializeField] private AnimationCurve _slideCurve = AnimationCurve.EaseInOut(0, 0, 1, 1);
        [SerializeField] private float _measurementAveragingTime = 0.15f;
        [SerializeField] private bool _stayWithinPlayerReach = false;
        public bool StayWithinPlayerReach { get { return _stayWithinPlayerReach; } set { _stayWithinPlayerReach = value; } }
        #endregion

        #region InternalMeasurementClasses
        private class MovementVelocityMeasurement {
            public MovementVelocityMeasurement(Vector3 movementVelocity, float time) {
                this.movementVelocity = movementVelocity;
                this.time = time;
            }

            public Vector3 movementVelocity;
            public float time;
        }

        private class RotationalVelocityMeasurement {
            public RotationalVelocityMeasurement(Quaternion rotationalVelocity, float time, float deltaTime) {
                this.rotationalVelocity = rotationalVelocity;
                this.time = time;
                this.deltaTime = deltaTime;
            }

            public Quaternion rotationalVelocity;
            public float time;
            public float deltaTime;
        }

        private class ScaleVelocityMeasurement {
            public ScaleVelocityMeasurement(float scaleVelocity, float time) {
                this.scaleVelocity = scaleVelocity;
                this.time = time;
            }

            public float scaleVelocity;
            public float time;
        }
        #endregion

        #region Other methods
        private void SetLocked(bool locked) {
            _allowMove = _allowRotate = _allowScale = _allowSlide = !locked;
        }

        public void StopAllSliding() {
            StopMovementSliding();
            StopRotationSliding();
            StopScaleSliding();
        }

        private void StopMovementSliding() {
            _movementVelocityFadeCounter = _movementVelocityFadeTime;
            _movementVelocity = Vector3.zero;
            _startMovementVelocityMagnitude = _movementVelocityMagnitude = 0.0f;
        }

        private void StopRotationSliding() {
            _rotationalVelocityFadeCounter = _rotationalVelocityFadeTime;
            _rotationalDifference = Quaternion.identity;
            _startRotationalAngleVelocity = _rotationalAngleVelocity = 0.0f;
        }

        private void StopScaleSliding() {
            _scaleVelocityFadeCounter = _scaleVelocityFadeTime;
            _startScaleVelocity = _scaleVelocity = 0;
        }

        public void ToggleLockRotating() {
            if(!_lockedRotating) {
                _lockedRotationQuaternion = _rotationalDifference;
                _lockedRotationVelocity = _rotationalAngleVelocity;
                StopAllSliding();
                SetLocked(true);
                _lockedRotating = true;
            }
            else {
                SetLocked(false);
                _rotationalDifference = _lockedRotationQuaternion;
                _rotationalVelocityFadeCounter = _rotationalVelocityFadeTime;
                _startRotationalAngleVelocity = _rotationalAngleVelocity = _lockedRotationVelocity;
                _lockedRotating = false;
            }
        }
        #endregion

        #region Events
        protected void Awake() {
            InteractionManager.InteractionSourceDetected += InteractionManager_InteractionSourceDetected;
            InteractionManager.InteractionSourceLost += InteractionManager_InteractionSourceLost;
            InteractionManager.InteractionSourcePressed += InteractionManager_InteractionSourcePressed;
            InteractionManager.InteractionSourceReleased += InteractionManager_InteractionSourceReleased;
            InteractionManager.InteractionSourceUpdated += InteractionManager_InteractionSourceUpdated;

            _transformer = new GameObject(gameObject.name + " Transformer");
            _transformer.transform.parent = transform.parent;
            _transformer.transform.localScale = transform.localScale;
            transform.SetParent(_transformer.transform);
        }

        protected void Update() {
            if(!_isTransforming && _grabPoints.Count > 0 && !_lockedRotating) {
                StartCoroutine(TransformCoroutine());
            }
        }

        protected void LateUpdate() {
            Slide();
        }

        protected void OnDestroy() {
            transform.SetParent(_transformer.transform.parent);
            Destroy(_transformer);

            InteractionManager.InteractionSourceDetected -= InteractionManager_InteractionSourceDetected;
            InteractionManager.InteractionSourceLost -= InteractionManager_InteractionSourceLost;
            InteractionManager.InteractionSourcePressed -= InteractionManager_InteractionSourcePressed;
            InteractionManager.InteractionSourceReleased -= InteractionManager_InteractionSourceReleased;
            InteractionManager.InteractionSourceUpdated -= InteractionManager_InteractionSourceUpdated;
        }

        private void InteractionManager_InteractionSourceDetected(InteractionSourceDetectedEventArgs eventArgs) {
            if(eventArgs.state.source.kind == InteractionSourceKind.Hand) {
                Hand hand = new Hand();
                uint id = eventArgs.state.source.id;
                GameObject handGameObject = new GameObject("Hand " + id.ToString());
                hand.GameObject = handGameObject;
                hand.ID = id;
                _trackedHands.Add(hand);
            }
        }

        private void InteractionManager_InteractionSourceLost(InteractionSourceLostEventArgs eventArgs) {
            if(eventArgs.state.source.kind == InteractionSourceKind.Hand) {
                ReleaseHand(eventArgs.state.source.id);
                for(int i = _trackedHands.Count - 1; i >= 0; i--) {
                    if(_trackedHands[i].ID == eventArgs.state.source.id) {
                        Destroy(_trackedHands[i].GameObject);
                        _trackedHands[i] = null;
                        _trackedHands.RemoveAt(i);
                        return;
                    }
                }
            }
        }

        private void InteractionManager_InteractionSourcePressed(InteractionSourcePressedEventArgs eventArgs) {
            if(eventArgs.state.source.kind == InteractionSourceKind.Hand) {
                foreach(Hand h in _trackedHands) {
                    if(h.ID == eventArgs.state.source.id) {
                        if(!_grabPoints.Contains(h.GameObject.transform)) {
                            _grabPoints.Add(h.GameObject.transform);
                        }
                        return;
                    }
                }
            }
        }

        private void InteractionManager_InteractionSourceReleased(InteractionSourceReleasedEventArgs eventArgs) {
            if(eventArgs.state.source.kind == InteractionSourceKind.Hand) {
                ReleaseHand(eventArgs.state.source.id);
            }
        }

        private void ReleaseHand(uint id) {
            foreach(Hand h in _trackedHands) {
                if(h.ID == id) {
                    if(_grabPoints.Contains(h.GameObject.transform)) {
                        _grabPoints.Remove(h.GameObject.transform);
                    }
                    return;
                }
            }
        }

        private void InteractionManager_InteractionSourceUpdated(InteractionSourceUpdatedEventArgs eventArgs) {
            if(eventArgs.state.source.kind == InteractionSourceKind.Hand) {
                foreach(Hand h in _trackedHands) {
                    if(h.ID == eventArgs.state.source.id) {
                        Vector3 handPosition;
                        if(eventArgs.state.sourcePose.TryGetPosition(out handPosition)) {
                            h.GameObject.transform.position = handPosition;
                        }
                        return;
                    }
                }
            }
        }
        #endregion

        #region SlidingMethods
        private void UpdateMovementVelocityMeasurements(Vector3 latestMeasurement) {
            for(int i = _movementVelocityMeasurements.Count - 1; i >= 0; i--) {
                if(_movementVelocityMeasurements[i].time < Time.time - _measurementAveragingTime) {
                    _movementVelocityMeasurements.RemoveAt(i);
                }
            }

            _movementVelocityMeasurements.Add(new MovementVelocityMeasurement(latestMeasurement, Time.time));

            Vector3 average = Vector3.zero;
            foreach(MovementVelocityMeasurement mvm in _movementVelocityMeasurements) {
                average += mvm.movementVelocity;
            }
            average = average / _movementVelocityMeasurements.Count;

            _movementVelocity = average;
            _startMovementVelocityMagnitude = _movementVelocityMagnitude = _movementVelocity.magnitude;
            _movementVelocityFadeCounter = _movementVelocityFadeTime;
        }

        private void UpdateRotationalVelocityMeasurements(Quaternion latestMeasurement) {
            for(int i = _rotationalVelocityMeasurements.Count - 1; i >= 0; i--) {
                if(_rotationalVelocityMeasurements[i].time < Time.time - _measurementAveragingTime) {
                    _rotationalVelocityMeasurements.RemoveAt(i);
                }
            }

            _rotationalVelocityMeasurements.Add(new RotationalVelocityMeasurement(latestMeasurement, Time.time, Time.deltaTime));

            Quaternion average = Quaternion.identity;
            float averageDeltaTime = 0;
            foreach(RotationalVelocityMeasurement rvm in _rotationalVelocityMeasurements) {
                average *= rvm.rotationalVelocity;
                averageDeltaTime += rvm.deltaTime;
            }

            averageDeltaTime = averageDeltaTime / _rotationalVelocityMeasurements.Count;
            float angle = (Quaternion.Angle(Quaternion.identity, average) / _rotationalVelocityMeasurements.Count) / averageDeltaTime;

            _rotationalDifference = average;
            _startRotationalAngleVelocity = _rotationalAngleVelocity = angle;
            _rotationalVelocityFadeCounter = _rotationalVelocityFadeTime;
        }

        private void UpdateScaleVelocityMeasurements(float latestMeasurement) {
            for(int i = _scaleVelocityMeasurements.Count - 1; i >= 0; i--) {
                if(_scaleVelocityMeasurements[i].time < Time.time - _measurementAveragingTime) {
                    _scaleVelocityMeasurements.RemoveAt(i);
                }
            }

            _scaleVelocityMeasurements.Add(new ScaleVelocityMeasurement(latestMeasurement, Time.time));

            float average = 0;
            foreach(ScaleVelocityMeasurement svm in _scaleVelocityMeasurements) {
                average += svm.scaleVelocity;
            }
            average = average / _scaleVelocityMeasurements.Count;

            _startScaleVelocity = _scaleVelocity = average;
            _scaleVelocityFadeCounter = _scaleVelocityFadeTime;
        }

        private void Slide() {
            if(_lockedRotating) {
                Quaternion rotationTarget = _transformer.transform.localRotation * Quaternion.Inverse(_lockedRotationQuaternion);
                Quaternion newRotation = Quaternion.RotateTowards(_transformer.transform.localRotation, rotationTarget, _lockedRotationVelocity * Time.deltaTime);
                _transformer.transform.localRotation = newRotation;
            }
            else if(_allowSlide) {
                // Slide movement when not grabbing
                if((!_isTransforming) && _movementVelocityMagnitude > 0) {
                    _movementVelocityFadeCounter -= Time.deltaTime;
                    float progress = 1 - (_movementVelocityFadeCounter / _movementVelocityFadeTime);
                    _movementVelocityMagnitude = Mathf.Lerp(_startMovementVelocityMagnitude, 0, _slideCurve.Evaluate(progress));
                    _transformer.transform.position += _movementVelocity.normalized * _movementVelocityMagnitude * Time.deltaTime;
                }

                // Slide rotation when not grabbing with two hands
                if(_grabPoints.Count < 2 && _rotationalAngleVelocity > 0) {
                    _rotationalVelocityFadeCounter -= Time.deltaTime;
                    float progress = 1 - (_rotationalVelocityFadeCounter / _rotationalVelocityFadeTime);
                    _rotationalAngleVelocity = Mathf.Lerp(_startRotationalAngleVelocity, 0, _slideCurve.Evaluate(progress));

                    Quaternion rotationTarget = _transformer.transform.localRotation * Quaternion.Inverse(_rotationalDifference);
                    Quaternion newRotation = Quaternion.RotateTowards(_transformer.transform.localRotation, rotationTarget, _rotationalAngleVelocity * Time.deltaTime);
                    _transformer.transform.localRotation = newRotation;
                }

                // Slide scaling when not grabbing with two hands
                if(_grabPoints.Count < 2) {
                    _scaleVelocityFadeCounter -= Time.deltaTime;
                    float progress = 1 - (_scaleVelocityFadeCounter / _scaleVelocityFadeTime);
                    _scaleVelocity = Mathf.Lerp(_startScaleVelocity, 0, _slideCurve.Evaluate(progress));

                    float newScale = _transformer.transform.localScale.x * (1 + (_scaleVelocity * Time.deltaTime));

                    // Slide scale towards min or max value if outside
                    float clampSpeed = 1;
                    if(newScale > _maxScale) {
                        newScale = newScale - (newScale - _maxScale) * Time.deltaTime * clampSpeed;
                    }
                    if(newScale < _minScale) {
                        newScale = newScale + (_minScale - newScale) * Time.deltaTime * clampSpeed;
                    }
                    if(newScale > AbsoluteMaxScale) {
                        newScale = AbsoluteMaxScale;
                    }
                    if(newScale < AbsoluteMinScale) {
                        newScale = AbsoluteMinScale;
                    }

                    _transformer.transform.localScale = new Vector3(newScale, newScale, newScale);
                    transform.localScale = Vector3.one;
                }

                // Slide towards reachable distance when not grabbing
                if(!_isTransforming && _stayWithinPlayerReach) {
                    if(_playerEyes != null) {
                        float transformerRadius = _transformer.transform.lossyScale.x / 2;
                        float approximateEyeHeight = _playerEyes.transform.localPosition.y;
                        float approximateArmLength = approximateEyeHeight * 0.35f;
                        Vector3 approximateChestPosition = _playerEyes.transform.position - (_playerEyes.transform.up * approximateEyeHeight * 0.2f);
                        float distance = Vector3.Distance(transform.position, approximateChestPosition);
                        float amountOutOfReach = distance - (approximateArmLength + transformerRadius);
                        float moveSpeed = 1;
                        if(amountOutOfReach > 0) {
                            _transformer.transform.Translate((approximateChestPosition - transform.position) * (amountOutOfReach * Time.deltaTime * moveSpeed), Space.World);
                        }
                    }
                    else {
                        _playerEyes = Camera.main.transform;
                    }
                }
            }
        }
        #endregion

        #region Transformation
        private IEnumerator TransformCoroutine(bool continuingTransformation = false) {
            _isTransforming = true;

            transform.parent = _transformer.transform.parent;

            // INITIATE POSITION AND ROTATION
            if(_allowMove) {
                _transformer.transform.position = _grabPoints[0].position;
            }
            else {
                _transformer.transform.position = transform.position;
            }
            _transformer.transform.rotation = Quaternion.identity;
            transform.parent = _transformer.transform;

            Transform singleGrabHand = _grabPoints[0];

            // ONE HAND GRABBING TRANSFORMER, MOVE TRANSFORM
            while(_grabPoints.Count == 1) {
                if (_grabPoints[0] != singleGrabHand) {
                    // Swapped hands, move transformer without moving transform
                    transform.parent = _transformer.transform.parent;
                    _transformer.transform.position = _grabPoints[0].position;
                    transform.parent = _transformer.transform;
                    singleGrabHand = _grabPoints[0];
                }
                _oldPosition = _transformer.transform.position;

                if(_allowMove) {
                    // SET NEW POSITION
                    _transformer.transform.position = _grabPoints[0].position;
                }

                _movementVelocity = (_transformer.transform.position - _oldPosition) / Time.deltaTime;
                UpdateMovementVelocityMeasurements(_movementVelocity);

                yield return 0;
            }

            // RESET TRANSFORMER
            transform.parent = _transformer.transform.parent;
            _transformer.transform.rotation = Quaternion.identity;
            transform.parent = _transformer.transform;

            // TWO HANDS GRABBING. MOVE, ROTATE AND SCALE TRANSFORM
            if(_grabPoints.Count > 1) {
                // INITIATE POSITION
                transform.parent = _transformer.transform.parent;
                if(_allowMove) {
                    _transformer.transform.position = (_grabPoints[0].position + _grabPoints[1].position) / 2;
                }
                else {
                    _transformer.transform.position = transform.position;
                }

                // INITIATE ROTATION
                Vector3 startVectorBetweenControllers = (_grabPoints[0].position - _grabPoints[1].position).normalized;
                Quaternion startRotation = Quaternion.LookRotation(startVectorBetweenControllers, _transformer.transform.up);
                _transformer.transform.rotation = startRotation;

                // INITIATE VARIABLES FOR CALCULATING NEW ROTATION
                Quaternion newRotation = startRotation;
                Quaternion oldControllerRotation = Quaternion.Lerp(_grabPoints[0].rotation, _grabPoints[1].rotation, 0.5f);
                Quaternion newControllerRotation = oldControllerRotation;
                Quaternion controllerRotationDifference;
                Vector3 controllerRotationDifferenceEuler;
                Vector3 newVectorBetweenControllers = startVectorBetweenControllers;
                float twistAmount;
                float twistDegrees;

                // INITIATE SCALE
                float startControllerDistance = Vector3.Distance(_grabPoints[0].position, _grabPoints[1].position);
                float newControllerDistance = startControllerDistance;
                float startScale = _transformer.transform.localScale.x;
                float newScale = startScale * (newControllerDistance / startControllerDistance);

                // INITIATION DONE, PARENT TRANSFORM TO TRANSFORMER
                transform.parent = _transformer.transform;

                while(_grabPoints.Count > 1) {
                    _oldPosition = _transformer.transform.position;

                    if(_allowMove) {
                        // CALCULATE AND SET NEW POSITION
                        _transformer.transform.position = (_grabPoints[0].position + _grabPoints[1].position) / 2;
                    }

                    _movementVelocity = (_transformer.transform.position - _oldPosition) / Time.deltaTime;
                    UpdateMovementVelocityMeasurements(_movementVelocity);

                    // CALCULATE NEW ROTATION BASED ON VECTOR BETWEEN CONTROLLERS
                    newVectorBetweenControllers = (_grabPoints[0].position - _grabPoints[1].position).normalized;
                    newRotation = Quaternion.LookRotation(newVectorBetweenControllers, _transformer.transform.up);

                    // CALCULATE NEW ROTATION BASED ON TWISTING OF CONTROLLERS
                    oldControllerRotation = newControllerRotation;
                    newControllerRotation = Quaternion.Lerp(_grabPoints[0].rotation, _grabPoints[1].rotation, 0.5f);
                    controllerRotationDifference = oldControllerRotation * Quaternion.Inverse(newControllerRotation);
                    controllerRotationDifferenceEuler = controllerRotationDifference.eulerAngles;
                    controllerRotationDifferenceEuler = new Vector3(controllerRotationDifferenceEuler.x > 180 ? controllerRotationDifferenceEuler.x - 360 : controllerRotationDifferenceEuler.x, controllerRotationDifferenceEuler.y > 180 ? controllerRotationDifferenceEuler.y - 360 : controllerRotationDifferenceEuler.y, controllerRotationDifferenceEuler.z > 180 ? controllerRotationDifferenceEuler.z - 360 : controllerRotationDifferenceEuler.z);
                    twistAmount = Vector3.Dot(newVectorBetweenControllers, controllerRotationDifferenceEuler.normalized);
                    twistDegrees =
                        controllerRotationDifferenceEuler.x * twistAmount * (controllerRotationDifferenceEuler.x > 0 ? -1 : 1) +
                    controllerRotationDifferenceEuler.y * twistAmount * (controllerRotationDifferenceEuler.y > 0 ? -1 : 1) +
                    controllerRotationDifferenceEuler.z * twistAmount * (controllerRotationDifferenceEuler.z > 0 ? -1 : 1);
                    newRotation *= Quaternion.Euler(0, 0, twistDegrees);

                    // SET NEW ROTATION
                    if(controllerRotationDifference.w > 0.9f) // BUG: Occasionally the controllerRotationDifference quaternion snaps to weird values, ignore these
                    {
                        _oldRotation = _transformer.transform.localRotation;
                        if(_allowRotate) {
                            _transformer.transform.localRotation = newRotation;
                        }
                        else {
                            newRotation = _oldRotation;
                        }
                        _rotationalDifference = _oldRotation * Quaternion.Inverse(newRotation);
                        UpdateRotationalVelocityMeasurements(_rotationalDifference);
                    }

                    // CALCULATE AND SET NEW SCALE
                    newControllerDistance = Vector3.Distance(_grabPoints[0].position, _grabPoints[1].position);
                    newScale = startScale * (newControllerDistance / startControllerDistance);
                    newScale = Mathf.Clamp(newScale, AbsoluteMinScale, AbsoluteMaxScale);
                    _oldScale = _transformer.transform.localScale.x;
                    if(_allowScale) {
                        _transformer.transform.localScale = new Vector3(newScale, newScale, newScale);
                        transform.localScale = Vector3.one;
                    }
                    else {
                        newScale = _oldScale;
                    }
                    float scaleVelocity = ((newScale / _oldScale) - 1) / Time.deltaTime;
                    UpdateScaleVelocityMeasurements(scaleVelocity);

                    yield return 0;
                }

                if(!_transformerGhost) {
                    GameObject _transformerGhostGo = new GameObject("Transformer Ghost");
                    _transformerGhost = _transformerGhostGo.transform;
                }

                _transformerGhost.position = _transformer.transform.position;
                _transformerGhost.rotation = _transformer.transform.rotation;
                _transformerGhost.parent = transform;

                _doubleGrabReleaseTime = Time.time;
            }

            // GO TO BEGINNING IF STILL GRABBING SOMETHING
            if(_grabPoints.Count > 0 && !_lockedRotating) {
                StartCoroutine(TransformCoroutine(true));
            }
            else {
                float doubleReleaseTimeAllowance = 0.5f;
                if(Time.time < _doubleGrabReleaseTime + doubleReleaseTimeAllowance) {
                    transform.parent = _transformer.transform.parent;
                    _transformer.transform.position = _transformerGhost.position;
                    _transformer.transform.rotation = Quaternion.identity;
                    transform.parent = _transformer.transform;
                }
                _isTransforming = false;
            }
        }
        #endregion
    }
}
