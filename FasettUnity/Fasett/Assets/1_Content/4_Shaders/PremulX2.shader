// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Particles/Alpha Blended Premultiply Mul" {
Properties {
    _MainTex ("Particle Texture", 2D) = "white" {}
    _Mul ("Multiplier", float) = 1
   _InvFade ("Soft Particles Factor", Range(0.01,3.0)) = 1.0
}

Category {
    Tags { "Queue"="Transparent" "IgnoreProjector"="True" "RenderType"="Transparent" }
    Blend One One 
    ColorMask RGB
    Cull Off Lighting Off ZWrite Off Fog { Mode Off }

    SubShader {
        Pass {
        
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #pragma multi_compile_particles

            #include "UnityCG.cginc"

            sampler2D _MainTex;
            fixed4 _TintColor;
            fixed _Mul;

            struct appdata_t {
                float4 vertex : POSITION;
                fixed4 color : COLOR;
                float2 texcoord : TEXCOORD0;
            };

            struct v2f {
                float4 vertex : SV_POSITION;
                fixed4 color : COLOR;
                float2 texcoord : TEXCOORD0;
                #ifdef SOFTPARTICLES_ON
                float4 projPos : TEXCOORD1;
                #endif
            };
            
            float4 _MainTex_ST;

            v2f vert (appdata_t v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                #ifdef SOFTPARTICLES_ON
                o.projPos = ComputeScreenPos (o.vertex);
                COMPUTE_EYEDEPTH(o.projPos.z);
                #endif
                o.color = v.color;
                o.texcoord = TRANSFORM_TEX(v.texcoord,_MainTex);
                return o;
            }

            sampler2D_float _CameraDepthTexture;
            float _InvFade;
            
            fixed4 frag (v2f i) : SV_Target
            {
                #ifdef SOFTPARTICLES_ON
                float sceneZ = LinearEyeDepth (SAMPLE_DEPTH_TEXTURE_PROJ(_CameraDepthTexture, UNITY_PROJ_COORD(i.projPos)));
                float partZ = i.projPos.z;
                float fade = saturate (_InvFade * (sceneZ-partZ));
                i.color.a *= fade;
                #endif
                
                return i.color * _Mul * tex2D(_MainTex, i.texcoord) * i.color.a;
            }
            ENDCG 
        }
    }
}
}