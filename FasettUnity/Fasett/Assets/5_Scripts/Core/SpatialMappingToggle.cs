using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.WSA;
using UnityEngine.XR.WSA.Input;

namespace Fasett {
    public class SpatialMappingToggle : MonoBehaviour {
        [SerializeField] private SpatialMappingRenderer spatialMappingRenderer;
        private GestureRecognizer recognizer;

        private void Start() {
            // Set up our GestureRecognizer and listen for Tapped
            recognizer = new GestureRecognizer();
            recognizer.Tapped += ToggleRendering;
            recognizer.StartCapturingGestures();
        }

        private void ToggleRendering(TappedEventArgs eventArgs) {
            if (spatialMappingRenderer.renderState != SpatialMappingRenderer.RenderState.Occlusion)
                spatialMappingRenderer.renderState = SpatialMappingRenderer.RenderState.Occlusion;
            else
                spatialMappingRenderer.renderState = SpatialMappingRenderer.RenderState.Visualization;
        }
    }
}
