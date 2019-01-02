using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleAttractor : MonoBehaviour {
    [SerializeField] private Gradient _gradient;
    [SerializeField] private ParticleSystem _particleSystem;
    [SerializeField] private float _innerRadius;
    [SerializeField] private float _outerRadius;
    [SerializeField] private AnimationCurve _movement;

    [SerializeField] private TouchBasedTrigger _trigger;

    private void OnEnable() {
        _trigger.OnPressedChanged += AffectParticles;
    }

    private void OnDisable() {
        _trigger.OnPressedChanged -= AffectParticles;
    }

    private void AffectParticles(float amount) {
        Vector3 attractPoint = _particleSystem.transform.InverseTransformPoint(transform.position);
        Color color = _gradient.Evaluate(amount);
        float power = _movement.Evaluate(amount);

        ParticleSystem.Particle[] particles = new ParticleSystem.Particle[_particleSystem.particleCount];
        _particleSystem.GetParticles(particles);
        for (int i = 0; i< particles.Length; i++) {
            Vector3 dir = particles[i].position - attractPoint;
            if (dir.magnitude < _outerRadius) {
                float distance = Mathf.Clamp01(Mathf.InverseLerp(_innerRadius, _outerRadius, dir.magnitude));
                particles[i].position = Vector3.Lerp(particles[i].position, attractPoint, power* distance);
                particles[i].color = Color.Lerp(particles[i].color, color, amount* distance);
            }
        }
        _particleSystem.SetParticles(particles, particles.Length);
    }

    private void OnDrawGizmos() {
        Gizmos.color = _gradient == null ? Color.gray : _gradient.Evaluate(0);
        Gizmos.DrawWireSphere(transform.position, _innerRadius);
        Gizmos.color = _gradient == null ? Color.black : _gradient.Evaluate(1);
        Gizmos.DrawWireSphere(transform.position, _outerRadius);
    }
}
