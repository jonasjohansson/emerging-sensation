using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class SkyEffect : Effect {
        [SerializeField] private Transform _target;
        [SerializeField] private GameObject _content;
        [SerializeField] private Vector3 _mostAffectedScale;

        [SerializeField] private AudioSource _maxedLoopAudioSource;
        private float _maxedSourceStartVolume;

        private Vector3 _startScale;
        private Material _holeMaterial;
        private Material _edgeMaterial;
        
        protected override void Awake() {
            int effectNumber = int.Parse(Name[1].ToString());
            _maxedLoopAudioSource.time = (_maxedLoopAudioSource.clip.length / 4) * effectNumber;
            _maxedSourceStartVolume = _maxedLoopAudioSource.volume;
            _maxedLoopAudioSource.volume = 0;

            _startScale = _target.localScale;
            Renderer renderer = _target.GetComponent<Renderer>();
            _edgeMaterial = renderer.materials[0];
            _holeMaterial = renderer.materials[1];

            base.Awake();
        }

        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);
            value /= 255;

            _maxedLoopAudioSource.volume = _maxedSourceStartVolume * value;
            _target.localScale = Vector3.Lerp(_startScale, _mostAffectedScale, value);

            _edgeMaterial.SetFloat("_EndOfTunnelGlow", value);
            _holeMaterial.SetFloat("_EndOfTunnelGlow", value);

        }

        public override void SetVisibility(float visibility) {
            base.SetVisibility(visibility);
            _content.SetActive(visibility > 0);
        
        }
    }
}
