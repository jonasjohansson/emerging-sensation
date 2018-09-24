using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Input;

namespace Fasett {
    public class SpatialMappingToggle : MonoBehaviour {
        [SerializeField] private SpatialMappingRenderer spatialMappingRenderer;

        public void ToggleRendering() {
            if (spatialMappingRenderer.renderState != SpatialMappingRenderer.RenderState.Occlusion)
                spatialMappingRenderer.renderState = SpatialMappingRenderer.RenderState.Occlusion;
            else
                spatialMappingRenderer.renderState = SpatialMappingRenderer.RenderState.Visualization;
        }
    }
}
