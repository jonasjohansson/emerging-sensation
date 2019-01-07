// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Hidden/BrightnessContrast" 
{
    Properties
    {
        _MainTex ("", 2D) = "white" {}
        _Brightness ("X", Range(0,1)) = 1
        _Contrast ("Y", Range(0,1)) = 1
    }

    SubShader
    {

        ZTest Always Cull Off ZWrite Off Fog { Mode Off } //Rendering settings

        Pass
        {
              CGPROGRAM
              #pragma vertex vert
              #pragma fragment frag
              #include "UnityCG.cginc"
              //we include "UnityCG.cginc" to use the appdata_img struct

              struct v2f
              {
                   float4 pos : POSITION;
                   half2 uv : TEXCOORD0;
              };

              //Our Vertex Shader
              v2f vert (appdata_img v)
              {
                   v2f o;
                   o.pos = UnityObjectToClipPos (v.vertex);
                   o.uv = MultiplyUV (UNITY_MATRIX_TEXTURE0, v.texcoord.xy);
                   return o;
              }

              sampler2D _MainTex;
              float _Brightness;
              float _Contrast;

              //Our Fragment Shader
              fixed4 frag (v2f i) : COLOR
              {
                   fixed4 col = tex2D(_MainTex, i.uv) * _Brightness;
                   col = lerp(col, smoothstep(0,1,col), _Contrast);
                   return col;
              }
              ENDCG
        }
    }
    FallBack "Diffuse"
}
