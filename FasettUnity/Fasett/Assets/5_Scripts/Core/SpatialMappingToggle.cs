using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Input;

namespace Fasett {
    public class SpatialMappingToggle : MonoBehaviour {
        [SerializeField] private SpatialMappingRenderer spatialMappingRenderer;

        public void ToggleRendering() {
            if (spatialMappingRenderer.renderState != SpatialMappingRenderer.RenderState.None)
                spatialMappingRenderer.renderState = SpatialMappingRenderer.RenderState.None;
            else
                spatialMappingRenderer.renderState = SpatialMappingRenderer.RenderState.Visualization;
                spatialMappingRenderer.sphereRadius = 15;
                spatialMappingRenderer.halfBoxExtents = new Vector3(20, 20, 20);
        }
    }
}
