Shader "Fasett/Sky/SkyTunnelStencil1" {
    Properties {
        _MainTex ("MainTex", 2D) = "white" {}
        [HDR]_TintColor ("Color", Color) = (0.5,0.5,0.5,1)
        _XPan ("XPan", Float ) = 0.1
        _YPan ("YPan", Float ) = 0.1
        _EndOfTunnelGlow ("EndOfTunnelGlow", Float ) = 0
        _Visibility ("Visibility", Float ) = 1
        [HDR]_EndOfTunnel ("EndOfTunnel", Color) = (0.5,0.5,0.5,1)
        [HideInInspector]_Cutoff ("Alpha cutoff", Range(0,1)) = 0.5
    }
    SubShader {
        Tags {
            "IgnoreProjector"="True"
            "Queue"="Transparent"
            "RenderType"="Transparent"
        }
        Pass {
            Name "FORWARD"
            Tags {
                "LightMode"="ForwardBase"
            }
            Blend One One
            ZTest Always
            ZWrite Off
            
            Stencil {
                Ref 1
                Comp Equal
                ZFail Zero
            }
            
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"
            #pragma multi_compile_fwdbase
            #pragma multi_compile_fog
            #pragma only_renderers d3d9 d3d11 glcore gles gles3 metal 
            #pragma target 3.0
            uniform sampler2D _MainTex; uniform float4 _MainTex_ST;
            uniform float4 _TintColor;
            uniform float _XPan;
            uniform float _YPan;
            uniform float _EndOfTunnelGlow;
            uniform float _Visibility;
            uniform float4 _EndOfTunnel;
            
            struct VertexInput {
                float4 vertex : POSITION;
                float2 texcoord0 : TEXCOORD0;
                float2 texcoord1 : TEXCOORD1;
                float4 vertexColor : COLOR;
            };
            
            struct VertexOutput {
                float4 pos : SV_POSITION;
                float2 uv0 : TEXCOORD0;
                float2 uv1 : TEXCOORD1;
                float4 vertexColor : COLOR;
            };
            
            VertexOutput vert (VertexInput v) {
                VertexOutput o = (VertexOutput)0;
                o.uv0 = v.texcoord0;
                o.uv1 = v.texcoord1 + (float2(_XPan,_YPan)*_Time.r);
                o.vertexColor = v.vertexColor;
                o.pos = UnityObjectToClipPos( v.vertex );
                return o;
            }
            
            float4 frag(VertexOutput i) : COLOR {
                fixed4 _MainTex_var = tex2D(_MainTex,TRANSFORM_TEX(i.uv1, _MainTex));
                fixed storm = (_MainTex_var.r+_MainTex_var.g)*0.5;
                fixed3 emissive = ((storm*_TintColor.rgb*2.0)+(i.uv0.g*_EndOfTunnelGlow*_EndOfTunnel.rgb));
                fixed3 finalColor = emissive;
                fixed4 finalRGBA = fixed4(finalColor * _Visibility,(_MainTex_var.a*i.vertexColor.a*_TintColor.a));
                return finalRGBA;
            }
            ENDCG
        }
    }
}
