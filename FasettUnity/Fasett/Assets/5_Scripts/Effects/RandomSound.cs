using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace  Fasett {
    public class RandomSound : MonoBehaviour {
        [SerializeField] private AudioClip[] _audioClips;
        private AudioSource _audioSource;

        protected void Awake() {
            _audioSource = GetComponent<AudioSource>();
        }

        public void Play() {
            if (_audioSource && _audioClips.Length > 0) {
                _audioSource.clip = _audioClips[Random.Range(0, _audioClips.Length)];
                _audioSource.Play();
            }
        }
    }
}
