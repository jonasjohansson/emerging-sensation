using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EmitParticlesInColor : MonoBehaviour {
    [SerializeField] private ParticleSystem[] _systems;
    [SerializeField] private Color color;

	[ContextMenu("Test")]
	private void Test(){
        Color color = Random.ColorHSV(0, 1, 1, 1, 0.5f, 1);
		Emit(color, 30);
	}

    private void Emit(Color color, int amount) {
        // Any parameters we assign in emitParams will override the current system's when we call Emit.
        // Here we will override the start color and size.
        var emitParams = new ParticleSystem.EmitParams();
        emitParams.startColor = color;
        emitParams.startSize = 0.2f;
        emitParams.startLifetime = 6;
        foreach(var system in _systems) {
            system.Emit(emitParams, amount);
        }
    }
}
