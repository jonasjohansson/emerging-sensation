using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class SkyEffect : Effect {
        [SerializeField] private Transform _target;
        [SerializeField] private Vector3 _mostAffectedScale;

        private Vector3 _startScale;
        private Material _holeMaterial;
        private Material _edgeMaterial;
        
        protected override void Awake() {
            _startScale = _target.localScale;
            Renderer renderer = _target.GetComponent<Renderer>();
            _edgeMaterial = renderer.materials[0];
            _holeMaterial = renderer.materials[1];

            base.Awake();
        }

        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);

            _target.localScale = Vector3.Lerp(_startScale, _mostAffectedScale, value);

            _edgeMaterial.SetFloat("_EndOfTunnelGlow", value);
            _holeMaterial.SetFloat("_EndOfTunnelGlow", value);

        }
    }
}
