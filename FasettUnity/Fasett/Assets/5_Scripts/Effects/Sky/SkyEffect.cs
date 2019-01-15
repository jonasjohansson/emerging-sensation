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

        private bool _isVisible;
        private float _rawValue;
        private float _smoothedValue;
        [SerializeField] private float _smoothPower;

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
            _rawValue = value / 255;
        }

        protected override void Update() {
            base.Update();
            if (_isVisible) {
                _smoothedValue = Mathf.Lerp(_smoothedValue, _rawValue, Time.deltaTime * _smoothPower);

                _maxedLoopAudioSource.volume = _maxedSourceStartVolume * _smoothedValue;
                _target.localScale = Vector3.Lerp(_startScale, _mostAffectedScale, _smoothedValue);

                _edgeMaterial.SetFloat("_EndOfTunnelGlow", _smoothedValue);
                _holeMaterial.SetFloat("_EndOfTunnelGlow", _smoothedValue);
            }
        }


        public override void SetVisibility(float visibility) {
            base.SetVisibility(visibility);
            _isVisible = visibility > 0;
            _content.SetActive(_isVisible);
        
        }
    }
}
