using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {

    public class WaterController : EffectController {
        [SerializeField] private WaterOrganism[] _organisms;
        [SerializeField] private ParticleSystem _particles;

        protected override void OnEnable() {
            base.OnEnable();
            _organisms = GetComponentsInChildren<WaterOrganism>(false);
            foreach (WaterOrganism organism in _organisms) {
                organism.Setup(_effects);
            }
        }

        protected override void VisibilityChanged(float visibility) {
            base.VisibilityChanged(visibility);
            for (int i = 0; i < _organisms.Length; i++) {
                _organisms[i].gameObject.SetActive(visibility > 0);
            }
            _particles.gameObject.SetActive(visibility > 0);
        }

        private void OnDisable() {
            foreach (WaterOrganism organism in _organisms) {
                organism.End();
            }
        }

        protected override void CenterObjects(Vector3 center) {
            base.CenterObjects(center);
            foreach (WaterOrganism organism in _organisms) {
                organism.SetCenterpoint(center);
            }
            _particles.transform.position = center;
        }
    }
}