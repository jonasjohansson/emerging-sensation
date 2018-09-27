using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class ParticlesAndSound : Effect {
        [SerializeField] private ParticleSystem _particleSystem;
        private float _startEmission;

        protected override void Awake() {
            base.Awake();
            _startEmission = _particleSystem.emission.rateOverTimeMultiplier;
        }

        public override void SetValue(float value) {
            ParticleSystem.EmissionModule emissionModule = _particleSystem.emission;
            emissionModule.rateOverTimeMultiplier = _startEmission * value;
        }
    }
}
