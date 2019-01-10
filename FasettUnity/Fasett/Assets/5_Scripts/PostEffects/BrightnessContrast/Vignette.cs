using UnityEngine;
using UnityStandardAssets.ImageEffects;
using System;

[ExecuteInEditMode]
public class Vignette : ImageEffectBase{
    [SerializeField] [Range(0, 1)] private float _amount = 1;
    [SerializeField] [Range(0, 1)] private float _brigthness = 1;
    [SerializeField] private Material _vignetteMaterial;
    
    // Called by camera to apply image effect
    void OnRenderImage (RenderTexture source, RenderTexture destination){
        _vignetteMaterial.SetFloat("_Amount", _amount);
        _vignetteMaterial.SetFloat("_Brightness", _brigthness);

        Graphics.Blit (source, destination, _vignetteMaterial);
	}
}
