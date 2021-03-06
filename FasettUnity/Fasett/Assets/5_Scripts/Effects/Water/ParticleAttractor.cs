﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett { 
    public class ParticleAttractor : MonoBehaviour {
        [SerializeField] private Gradient _gradient;
        [SerializeField] private ParticleSystem _particleSystem;
        [SerializeField] private float _innerRadius;
        [SerializeField] private float _outerRadius;
        [SerializeField] private AnimationCurve _movement;
        [SerializeField] private AnimationCurve _pullPower;
        [SerializeField] private float _fullGlow = 1;
        [SerializeField] private float _power = 1;
        
        [SerializeField] private WaterEffect _trigger;

        /*
        private List<Vector3> From = new List<Vector3>();
        private List<Vector3> To = new List<Vector3>();
        */

        private void OnEnable() {
            _trigger.OnPressedChanged += AffectParticles;
        }
        
        private void OnDisable() {
            _trigger.OnPressedChanged -= AffectParticles;
        }
        
        
        private void AffectParticles(WaterEffect trigger) {
            Vector3 attractPoint = _particleSystem.transform.InverseTransformPoint(transform.position);
            float power = _movement.Evaluate(trigger.PressAmount);
            Color color = Color.Lerp(Color.grey *.5f, trigger.Color * _fullGlow, power);
            
            ParticleSystem.Particle[] particles = new ParticleSystem.Particle[_particleSystem.particleCount];
            _particleSystem.GetParticles(particles);
            /*
            From.Clear();
            To.Clear();
            */
            for (int i = 0; i< particles.Length; i++) {
                Vector3 dir = particles[i].position - attractPoint;
                if (dir.magnitude < _outerRadius) {
                    float distance = Mathf.Clamp01(Mathf.InverseLerp(-_innerRadius, _outerRadius, dir.magnitude));
                    Vector3 targetPos = particles[i].position - dir.normalized * distance;
                    float pull = _pullPower.Evaluate(distance) * Time.deltaTime * _power;
                    
                    particles[i].position = Vector3.Lerp(particles[i].position, targetPos, pull);
                    particles[i].color = Color.Lerp(particles[i].color, color, pull);

                    /*
                    From.Add(_particleSystem.transform.TransformPoint(particles[i].position));
                    To.Add(_particleSystem.transform.TransformPoint(targetPos));
                    */                   
                }
            }
            _particleSystem.SetParticles(particles, particles.Length);
        }
        
        private void OnDrawGizmosSelected() {
            Gizmos.color = _gradient == null ? Color.gray : _gradient.Evaluate(0);
            Gizmos.DrawWireSphere(transform.position, _innerRadius);
            Gizmos.color = _gradient == null ? Color.black : _gradient.Evaluate(1);
            Gizmos.DrawWireSphere(transform.position, _outerRadius);

            Gizmos.color = Color.blue;
            /*
            for (int i = 0; i<From.Count; i++) {
                Gizmos.DrawLine(From[i], To[i]);
            }
            */
        }
    }
    
}