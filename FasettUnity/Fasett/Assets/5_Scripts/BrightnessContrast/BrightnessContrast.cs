using UnityEngine;
using UnityStandardAssets.ImageEffects;
using System;

[ExecuteInEditMode]
public class BrightnessContrast : ImageEffectBase{
	[SerializeField][Range(0, 1)] private float _brightness;
	[SerializeField][Range(0, 1)] private float _contrast;


	// Called by camera to apply image effect
	void OnRenderImage (RenderTexture source, RenderTexture destination){
		material.SetFloat("_Brightness", _brightness);
		material.SetFloat("_Contrast", _contrast);
	
		Graphics.Blit (source, destination, material);
	}
}
