using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class ParticlesAndSound : Effect {
        [SerializeField] private ParticleSystem _particleSystem;
        [SerializeField] private AudioSource _audioSource;
        private float _startEmission;
        private float _startVolume;

        protected override void Awake() {
            base.Awake();
            _startEmission = _particleSystem.emission.rateOverTimeMultiplier;
            _startVolume = _audioSource.volume;
        }

        public override void UpdateEffect(float value) {
            base.UpdateEffect(value);
            ParticleSystem.EmissionModule emissionModule = _particleSystem.emission;
            emissionModule.rateOverTimeMultiplier = _startEmission * value;
            _audioSource.volume = _startVolume * value;
        }
    }
}
