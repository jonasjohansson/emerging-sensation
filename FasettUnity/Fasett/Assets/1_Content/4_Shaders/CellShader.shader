Shader "Unlit/CellShader" {
    Properties {
        [HDR]_Tint ("Tint", Color) = (1,0,0,1)
        _Fresnel ("Fresnel", Range(0, 10)) = 0
        _CellRamp ("CellRamp", 2D) = "white" {}
        _Wobble ("Wobble", Float ) = 0
        _Particles ("Particles", 2D) = "white" {}
        _Offset ("Offset", Float ) = 0
        _Frequency ("Frequency", Float ) = 1
        _Amplitude ("Amplitude", Float ) = 1
    }
    SubShader {
        Tags {
            "RenderType"="Opaque"
        }
        LOD 100
        Pass {
            Name "FORWARD"
            Tags {
                "LightMode"="ForwardBase"
            }
            
            
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"
            #pragma multi_compile_fwdbase_fullshadows
            #pragma only_renderers d3d9 d3d11 glcore gles gles3 metal 
            #pragma target 3.0
            uniform float4 _Tint;
            uniform float _Fresnel;
            uniform sampler2D _CellRamp; uniform float4 _CellRamp_ST;
            uniform float _Wobble;
            uniform sampler2D _Particles; uniform float4 _Particles_ST;
            uniform float _Offset;
            uniform float _Frequency;
            uniform float _Amplitude;
            
            struct VertexInput {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
                float2 texcoord0 : TEXCOORD0;
            };
            
            struct VertexOutput {
                float4 pos : SV_POSITION;
                float2 uv0 : TEXCOORD0;
                float2 uv1 : TEXCOORD3;
                float2 uv2 : TEXCOORD4;
                fixed glow : TEXCOORD5;
                float4 posWorld : TEXCOORD1;
                float3 normalDir : TEXCOORD2;
            };
            
            VertexOutput vert (VertexInput v) {
                VertexOutput o = (VertexOutput)0;
                o.uv0 = v.texcoord0;
                o.normalDir = UnityObjectToWorldNormal(v.normal);
                
                fixed wobble = _Time.r*_Wobble;
                fixed xOffset = ((0.1*wobble)+(sin((wobble*4.0))*0.2));
                fixed yOffset = ((wobble*0.1)+(sin((wobble*4.0))*0.2));
                o.uv1 = (o.uv0+fixed2(xOffset,yOffset));
                o.uv2 = (o.uv0+fixed2(yOffset,xOffset));

                fixed partOffset = tex2Dlod(_Particles,float4(TRANSFORM_TEX(o.uv1, _Particles),0.0,0)).g;
                v.vertex.xyz += (v.normal*_Offset*(0.5-(1.0 - partOffset)));
                o.posWorld = mul(unity_ObjectToWorld, v.vertex);
                o.pos = UnityObjectToClipPos( v.vertex );
                
                o.glow = ((_Amplitude*sin(((6.28318530718*_Frequency*_Time.g)+((o.posWorld.r+o.posWorld.g)*2.0))))+2.0);
                
                return o;
            }
            
            float4 frag(VertexOutput i) : COLOR {
                i.normalDir = normalize(i.normalDir);
                float3 viewDirection = normalize(_WorldSpaceCameraPos.xyz - i.posWorld.xyz);
                
                fixed2 fresnel = float2(pow(1.0-max(0,dot(i.normalDir, viewDirection)),_Fresnel),0.5);
                fixed _cellRamp = tex2D(_CellRamp,TRANSFORM_TEX(fresnel, _CellRamp)).g;
                
                
                fixed part1 = tex2D(_Particles,TRANSFORM_TEX(i.uv1, _Particles)).g;
                fixed part2 = tex2D(_Particles,TRANSFORM_TEX(i.uv2, _Particles)).g;
                fixed particles = part1 * part2 * 2.0;
                
                fixed3 emissive = (_cellRamp*_Tint.rgb*i.glow*particles);
                return fixed4(emissive,1);
            }
            ENDCG
        }
    }
    FallBack "Diffuse"
}
