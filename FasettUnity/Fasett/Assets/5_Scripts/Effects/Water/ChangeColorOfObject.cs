using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeColorOfObject : MonoBehaviour {
    [SerializeField] private Gradient _gradient;
    [SerializeField] private WaterTrigger _trigger;

    private Mesh _mesh;
    private Color32[] _colors;

    private void Awake() {
        _mesh = GetComponent<MeshFilter>().mesh;
        _colors = new Color32[_mesh.vertexCount];
        SetColor(_trigger);
    }

    private void OnEnable() {
        _trigger.OnPressedChanged += SetColor;
    }

    private void OnDisable() {
        _trigger.OnPressedChanged -= SetColor;
    }

    private void SetColor(WaterTrigger trigger) {
        Color color = _gradient.Evaluate(trigger.PressAmount);
        for (int i = 0; i<_colors.Length; i++) {
            _colors[i] = color;
        }
        _mesh.colors32 = _colors;
    }
}
