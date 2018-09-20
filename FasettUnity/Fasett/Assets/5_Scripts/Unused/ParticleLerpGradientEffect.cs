using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleLerpGradientEffect : MonoBehaviour {
	[SerializeField] private FloatInput _sender;
	[SerializeField] private ParticleSystem _particleSystem;
	[SerializeField] private Gradient _lowGradient;
	[SerializeField] private Gradient _highGradient;

#pragma warning disable 0414 // Disable "never used" warning - we use it to visualize in inspector
    [SerializeField] private Gradient _grad;
#pragma warning restore 0414

    protected void OnEnable(){
		_sender.OnNewValue += NewValue;
		NewValue(_sender.Value);
	}

	protected void OnDisable(){
		_sender.OnNewValue -= NewValue;
	}

	private void NewValue(float value){
		Gradient gradient = _grad = LerpGradient(value);
		ParticleSystem.ColorOverLifetimeModule colorOverLifeTimeModule = _particleSystem.colorOverLifetime;
		colorOverLifeTimeModule.color = gradient;
	}

	private Gradient LerpGradient(float value){
		int alphaLength = _lowGradient.alphaKeys.Length;
		int colorLength = _lowGradient.colorKeys.Length;
		GradientAlphaKey[] alphaKeys = new GradientAlphaKey[alphaLength];
		GradientColorKey[] colorKeys = new GradientColorKey[colorLength];

		for (int i = 0; i<alphaLength; i++){
			alphaKeys[i] = LerpAlphaKey(_lowGradient.alphaKeys[i], _highGradient.alphaKeys[i], value);
		}
		for (int i = 0; i<colorLength; i++){
			colorKeys[i] = LerpColorKey(_lowGradient.colorKeys[i], _highGradient.colorKeys[i], value);
		}

		Gradient gradient = new Gradient();
		gradient.alphaKeys = alphaKeys;
		gradient.colorKeys = colorKeys;
		gradient.mode = GradientMode.Blend;
		return gradient;
	}

	private GradientAlphaKey LerpAlphaKey(GradientAlphaKey low, GradientAlphaKey high, float value){
		float time = Mathf.Lerp(low.time, high.time, value);
		float alpha = Mathf.Lerp(low.alpha, high.alpha, value);
		return new GradientAlphaKey(alpha, time);
	}

	private GradientColorKey LerpColorKey(GradientColorKey low, GradientColorKey high, float value){
		float time = Mathf.Lerp(low.time, high.time, value);
		Color color = Color.Lerp(low.color, high.color, value);
		return new GradientColorKey(color, time);
	}
}
