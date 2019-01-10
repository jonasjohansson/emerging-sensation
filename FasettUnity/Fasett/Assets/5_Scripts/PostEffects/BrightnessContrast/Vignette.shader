// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Hidden/Vignette" 
{
    Properties
    {
        _MainTex ("MainTex", 2D) = "white" {}
        _Vignette ("Vignette", 2D) = "white" {}
        _Amount ("Amount", Range(0,1)) = 1
        _Brightness ("Brightness", Range(0,1)) = 1
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
              sampler2D _Vignette;
              float _Amount;
			  float _Brightness;

              //Our Fragment Shader
              fixed4 frag (v2f i) : COLOR
              {
                   fixed3 col = tex2D(_MainTex, i.uv).rgb;
                   fixed4 vig = tex2D(_Vignette, i.uv);
				   fixed mul = lerp(1,1-_Amount, vig.a);
                   return fixed4(col.rgb * mul * _Brightness,1);
              }
              ENDCG
        }
    }
    FallBack "Diffuse"
}
