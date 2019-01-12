using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Fasett {
    public class DebugLine : MonoBehaviour {
        [SerializeField] private TextMesh _text;
        [SerializeField] private float _textDistance;


        [SerializeField] private LineRenderer _line;
        [SerializeField] private Transform _cameraSource;
        [SerializeField] private Transform _target;

        [SerializeField] private Vector3 _offset;

        [ContextMenu("Update")]
        private void Update() {
            Vector3[] positions = new Vector3[3] {
                _cameraSource.position,
                _target.position + _offset,
                _target.position
            };

            _line.SetPositions(positions);

            _text.transform.position = positions[0] + (positions[1]-positions[0]).normalized * _textDistance +  Vector3.up * .1f;
            _text.transform.LookAt(positions[1]);
        }
    }
}
