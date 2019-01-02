// Shader created with Shader Forge v1.38 
// Shader Forge (c) Freya Holmer - http://www.acegikmo.com/shaderforge/
// Note: Manually altering this data may prevent you from opening it in Shader Forge
/*SF_DATA;ver:1.38;sub:START;pass:START;ps:flbk:,iptp:0,cusa:False,bamd:0,cgin:,lico:1,lgpr:1,limd:0,spmd:1,trmd:0,grmd:0,uamb:True,mssp:True,bkdf:False,hqlp:False,rprd:False,enco:False,rmgx:True,imps:True,rpth:0,vtps:0,hqsc:True,nrmq:1,nrsp:0,vomd:0,spxs:False,tesm:0,olmd:1,culm:0,bsrc:0,bdst:1,dpts:6,wrdp:True,dith:0,atcv:False,rfrpo:True,rfrpn:Refraction,coma:15,ufog:True,aust:False,igpj:False,qofs:0,qpre:1,rntp:1,fgom:False,fgoc:False,fgod:False,fgor:False,fgmd:0,fgcr:0.5,fgcg:0.5,fgcb:0.5,fgca:1,fgde:0.01,fgrn:0,fgrf:300,stcl:False,atwp:False,stva:128,stmr:255,stmw:255,stcp:6,stps:0,stfa:0,stfz:0,ofsf:0,ofsu:0,f2p0:False,fnsp:False,fnfb:False,fsmp:False;n:type:ShaderForge.SFN_Final,id:815,x:32922,y:32686,varname:node_815,prsc:2|emission-95-OUT,voffset-1408-OUT;n:type:ShaderForge.SFN_Fresnel,id:4828,x:31929,y:32157,varname:node_4828,prsc:2|EXP-8748-OUT;n:type:ShaderForge.SFN_Color,id:9946,x:31955,y:32413,ptovrint:False,ptlb:Tint,ptin:_Tint,varname:node_9946,prsc:2,glob:False,taghide:False,taghdr:True,tagprd:False,tagnsco:False,tagnrm:False,c1:1,c2:0,c3:0,c4:1;n:type:ShaderForge.SFN_Slider,id:8748,x:31560,y:32173,ptovrint:False,ptlb:Fresnel,ptin:_Fresnel,varname:node_8748,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,min:0,cur:0,max:10;n:type:ShaderForge.SFN_Tex2d,id:3383,x:32352,y:32227,ptovrint:False,ptlb:CellRamp,ptin:_CellRamp,varname:node_3383,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,ntxv:0,isnm:False|UVIN-9880-OUT;n:type:ShaderForge.SFN_Append,id:9880,x:32149,y:32202,varname:node_9880,prsc:2|A-4828-OUT,B-5278-OUT;n:type:ShaderForge.SFN_Vector1,id:5278,x:31895,y:32294,varname:node_5278,prsc:2,v1:0.5;n:type:ShaderForge.SFN_Multiply,id:95,x:32552,y:32599,varname:node_95,prsc:2|A-3383-RGB,B-9946-RGB,C-1120-OUT,D-8498-OUT;n:type:ShaderForge.SFN_Vector1,id:8387,x:32308,y:32428,varname:node_8387,prsc:2,v1:2;n:type:ShaderForge.SFN_Tex2d,id:9788,x:31955,y:32656,varname:node_9788,prsc:2,ntxv:0,isnm:False|UVIN-3488-OUT,TEX-6213-TEX;n:type:ShaderForge.SFN_Sin,id:3563,x:30995,y:32485,varname:node_3563,prsc:2|IN-6115-OUT;n:type:ShaderForge.SFN_Time,id:2764,x:30279,y:32696,varname:node_2764,prsc:2;n:type:ShaderForge.SFN_Add,id:2078,x:31262,y:32653,varname:node_2078,prsc:2|A-3982-OUT,B-7956-OUT;n:type:ShaderForge.SFN_Multiply,id:6115,x:30833,y:32485,varname:node_6115,prsc:2|A-3690-OUT,B-195-OUT;n:type:ShaderForge.SFN_Vector1,id:195,x:30642,y:32505,varname:node_195,prsc:2,v1:4;n:type:ShaderForge.SFN_Vector1,id:7472,x:30655,y:33032,varname:node_7472,prsc:2,v1:4;n:type:ShaderForge.SFN_Multiply,id:3173,x:30846,y:33012,varname:node_3173,prsc:2|A-3690-OUT,B-7472-OUT;n:type:ShaderForge.SFN_Sin,id:1350,x:31008,y:33012,varname:node_1350,prsc:2|IN-3173-OUT;n:type:ShaderForge.SFN_Add,id:2728,x:31274,y:32813,varname:node_2728,prsc:2|A-3404-OUT,B-6985-OUT;n:type:ShaderForge.SFN_Relay,id:3690,x:30688,y:32751,varname:node_3690,prsc:2|IN-4742-OUT;n:type:ShaderForge.SFN_Multiply,id:3982,x:31047,y:32653,varname:node_3982,prsc:2|A-7912-OUT,B-3690-OUT;n:type:ShaderForge.SFN_Vector1,id:7912,x:30833,y:32653,varname:node_7912,prsc:2,v1:0.1;n:type:ShaderForge.SFN_Vector1,id:2504,x:30846,y:32836,varname:node_2504,prsc:2,v1:0.1;n:type:ShaderForge.SFN_Multiply,id:3404,x:31047,y:32813,varname:node_3404,prsc:2|A-3690-OUT,B-2504-OUT;n:type:ShaderForge.SFN_Append,id:7659,x:31447,y:32736,varname:node_7659,prsc:2|A-2078-OUT,B-2728-OUT;n:type:ShaderForge.SFN_Add,id:3488,x:31679,y:32629,varname:node_3488,prsc:2|A-2031-UVOUT,B-7659-OUT;n:type:ShaderForge.SFN_TexCoord,id:2031,x:31451,y:32588,varname:node_2031,prsc:2,uv:0,uaff:False;n:type:ShaderForge.SFN_Multiply,id:4742,x:30481,y:32847,varname:node_4742,prsc:2|A-2764-TSL,B-9008-OUT;n:type:ShaderForge.SFN_ValueProperty,id:9008,x:30222,y:32999,ptovrint:False,ptlb:node_9008,ptin:_node_9008,varname:node_9008,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,v1:0;n:type:ShaderForge.SFN_Multiply,id:6985,x:31196,y:33071,varname:node_6985,prsc:2|A-1350-OUT,B-5275-OUT;n:type:ShaderForge.SFN_Vector1,id:5275,x:31079,y:33230,varname:node_5275,prsc:2,v1:0.2;n:type:ShaderForge.SFN_Multiply,id:7956,x:31240,y:32306,varname:node_7956,prsc:2|A-3563-OUT,B-8312-OUT;n:type:ShaderForge.SFN_Vector1,id:8312,x:31051,y:32257,varname:node_8312,prsc:2,v1:0.2;n:type:ShaderForge.SFN_Multiply,id:1408,x:32664,y:33066,varname:node_1408,prsc:2|A-2539-OUT,B-5558-OUT,C-8093-OUT;n:type:ShaderForge.SFN_Tex2dAsset,id:6213,x:31679,y:32788,ptovrint:False,ptlb:Particles,ptin:_Particles,varname:node_6213,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,ntxv:0,isnm:False;n:type:ShaderForge.SFN_Multiply,id:9767,x:32174,y:32798,varname:node_9767,prsc:2|A-9788-RGB,B-5006-RGB,C-2502-OUT;n:type:ShaderForge.SFN_Relay,id:8498,x:32375,y:32876,varname:node_8498,prsc:2|IN-9767-OUT;n:type:ShaderForge.SFN_TexCoord,id:3758,x:31530,y:33069,varname:node_3758,prsc:2,uv:0,uaff:False;n:type:ShaderForge.SFN_Add,id:7347,x:31758,y:33069,varname:node_7347,prsc:2|A-3758-UVOUT,B-331-OUT;n:type:ShaderForge.SFN_Append,id:331,x:31461,y:32885,varname:node_331,prsc:2|A-2728-OUT,B-2078-OUT;n:type:ShaderForge.SFN_Tex2d,id:5006,x:31956,y:33010,varname:node_5006,prsc:2,ntxv:0,isnm:False|UVIN-7347-OUT,TEX-6213-TEX;n:type:ShaderForge.SFN_Vector1,id:2502,x:31882,y:32896,varname:node_2502,prsc:2,v1:2;n:type:ShaderForge.SFN_ValueProperty,id:5558,x:32185,y:33500,ptovrint:False,ptlb:Offset,ptin:_Offset,varname:node_5558,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,v1:0;n:type:ShaderForge.SFN_NormalVector,id:2539,x:32622,y:33382,prsc:2,pt:False;n:type:ShaderForge.SFN_Desaturate,id:2478,x:32316,y:32971,varname:node_2478,prsc:2|COL-9788-RGB;n:type:ShaderForge.SFN_OneMinus,id:3492,x:32300,y:33098,varname:node_3492,prsc:2|IN-2478-OUT;n:type:ShaderForge.SFN_Subtract,id:8093,x:32316,y:33235,varname:node_8093,prsc:2|A-6347-OUT,B-3492-OUT;n:type:ShaderForge.SFN_Vector1,id:6347,x:32110,y:33283,varname:node_6347,prsc:2,v1:0.5;n:type:ShaderForge.SFN_Vector1,id:7453,x:32096,y:33187,varname:node_7453,prsc:2,v1:1;n:type:ShaderForge.SFN_Time,id:5497,x:32316,y:31630,varname:node_5497,prsc:2;n:type:ShaderForge.SFN_Sin,id:3301,x:32617,y:31856,varname:node_3301,prsc:2|IN-6780-OUT;n:type:ShaderForge.SFN_ValueProperty,id:3539,x:32316,y:31576,ptovrint:False,ptlb:Frequency,ptin:_Frequency,varname:node_3539,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,v1:1;n:type:ShaderForge.SFN_ValueProperty,id:7139,x:32649,y:31800,ptovrint:False,ptlb:Amplitude,ptin:_Amplitude,varname:node_7139,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,v1:1;n:type:ShaderForge.SFN_Multiply,id:6780,x:32587,y:31529,varname:node_6780,prsc:2|A-6483-OUT,B-3539-OUT,C-5497-T;n:type:ShaderForge.SFN_Tau,id:6483,x:32349,y:31443,varname:node_6483,prsc:2;n:type:ShaderForge.SFN_Multiply,id:4562,x:32892,y:31840,varname:node_4562,prsc:2|A-7139-OUT,B-3301-OUT;n:type:ShaderForge.SFN_Add,id:1120,x:32711,y:32335,varname:node_1120,prsc:2|A-4562-OUT,B-8387-OUT;n:type:ShaderForge.SFN_Sin,id:2814,x:33019,y:31391,varname:node_2814,prsc:2|IN-9111-OUT;n:type:ShaderForge.SFN_Time,id:9314,x:32513,y:31108,varname:node_9314,prsc:2;n:type:ShaderForge.SFN_Multiply,id:4947,x:33063,y:31188,varname:node_4947,prsc:2|A-9111-OUT,B-8292-OUT;n:type:ShaderForge.SFN_Vector1,id:8292,x:32801,y:31133,varname:node_8292,prsc:2,v1:1.5;n:type:ShaderForge.SFN_Sin,id:6525,x:33278,y:31204,varname:node_6525,prsc:2|IN-4947-OUT;n:type:ShaderForge.SFN_Multiply,id:9502,x:33473,y:31204,varname:node_9502,prsc:2|A-6525-OUT,B-1364-OUT;n:type:ShaderForge.SFN_Vector1,id:1364,x:33316,y:31101,varname:node_1364,prsc:2,v1:4;n:type:ShaderForge.SFN_Add,id:4615,x:33673,y:31333,varname:node_4615,prsc:2|A-9502-OUT,B-8464-OUT;n:type:ShaderForge.SFN_Power,id:8464,x:33319,y:31372,varname:node_8464,prsc:2|VAL-2814-OUT,EXP-4150-OUT;n:type:ShaderForge.SFN_Vector1,id:4150,x:33069,y:31577,varname:node_4150,prsc:2,v1:63;n:type:ShaderForge.SFN_Multiply,id:9111,x:32761,y:31258,varname:node_9111,prsc:2|A-9314-T,B-3539-OUT;n:type:ShaderForge.SFN_Multiply,id:6534,x:33303,y:31785,varname:node_6534,prsc:2|A-7139-OUT,B-4883-OUT;n:type:ShaderForge.SFN_Max,id:4883,x:33625,y:31671,varname:node_4883,prsc:2|A-4615-OUT,B-225-OUT;n:type:ShaderForge.SFN_Vector1,id:225,x:33402,y:31666,varname:node_225,prsc:2,v1:0;proporder:9946-8748-3383-9008-6213-5558-3539-7139;pass:END;sub:END;*/

Shader "Unlit/CellShader" {
    Properties {
        [HDR]_Tint ("Tint", Color) = (1,0,0,1)
        _Fresnel ("Fresnel", Range(0, 10)) = 0
        _CellRamp ("CellRamp", 2D) = "white" {}
        _node_9008 ("node_9008", Float ) = 0
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
            ZTest Always
            
            
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"
            #pragma multi_compile_fwdbase_fullshadows
            #pragma multi_compile_fog
            #pragma only_renderers d3d9 d3d11 glcore gles 
            #pragma target 3.0
            uniform float4 _Tint;
            uniform float _Fresnel;
            uniform sampler2D _CellRamp; uniform float4 _CellRamp_ST;
            uniform float _node_9008;
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
                float4 posWorld : TEXCOORD1;
                float3 normalDir : TEXCOORD2;
                UNITY_FOG_COORDS(3)
            };
            VertexOutput vert (VertexInput v) {
                VertexOutput o = (VertexOutput)0;
                o.uv0 = v.texcoord0;
                o.normalDir = UnityObjectToWorldNormal(v.normal);
                float4 node_2764 = _Time;
                float node_3690 = (node_2764.r*_node_9008);
                float node_2078 = ((0.1*node_3690)+(sin((node_3690*4.0))*0.2));
                float node_2728 = ((node_3690*0.1)+(sin((node_3690*4.0))*0.2));
                float2 node_3488 = (o.uv0+float2(node_2078,node_2728));
                float4 node_9788 = tex2Dlod(_Particles,float4(TRANSFORM_TEX(node_3488, _Particles),0.0,0));
                v.vertex.xyz += (v.normal*_Offset*(0.5-(1.0 - dot(node_9788.rgb,float3(0.3,0.59,0.11)))));
                o.posWorld = mul(unity_ObjectToWorld, v.vertex);
                o.pos = UnityObjectToClipPos( v.vertex );
                UNITY_TRANSFER_FOG(o,o.pos);
                return o;
            }
            float4 frag(VertexOutput i) : COLOR {
                i.normalDir = normalize(i.normalDir);
                float3 viewDirection = normalize(_WorldSpaceCameraPos.xyz - i.posWorld.xyz);
                float3 normalDirection = i.normalDir;
////// Lighting:
////// Emissive:
                float2 node_9880 = float2(pow(1.0-max(0,dot(normalDirection, viewDirection)),_Fresnel),0.5);
                float4 _CellRamp_var = tex2D(_CellRamp,TRANSFORM_TEX(node_9880, _CellRamp));
                float4 node_5497 = _Time;
                float4 node_2764 = _Time;
                float node_3690 = (node_2764.r*_node_9008);
                float node_2078 = ((0.1*node_3690)+(sin((node_3690*4.0))*0.2));
                float node_2728 = ((node_3690*0.1)+(sin((node_3690*4.0))*0.2));
                float2 node_3488 = (i.uv0+float2(node_2078,node_2728));
                float4 node_9788 = tex2D(_Particles,TRANSFORM_TEX(node_3488, _Particles));
                float2 node_7347 = (i.uv0+float2(node_2728,node_2078));
                float4 node_5006 = tex2D(_Particles,TRANSFORM_TEX(node_7347, _Particles));
                float3 emissive = (_CellRamp_var.rgb*_Tint.rgb*((_Amplitude*sin((6.28318530718*_Frequency*node_5497.g)))+2.0)*(node_9788.rgb*node_5006.rgb*2.0));
                float3 finalColor = emissive;
                fixed4 finalRGBA = fixed4(finalColor,1);
                UNITY_APPLY_FOG(i.fogCoord, finalRGBA);
                return finalRGBA;
            }
            ENDCG
        }
        Pass {
            Name "ShadowCaster"
            Tags {
                "LightMode"="ShadowCaster"
            }
            Offset 1, 1
            Cull Back
            
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"
            #include "Lighting.cginc"
            #pragma fragmentoption ARB_precision_hint_fastest
            #pragma multi_compile_shadowcaster
            #pragma multi_compile_fog
            #pragma only_renderers d3d9 d3d11 glcore gles 
            #pragma target 3.0
            uniform float _node_9008;
            uniform sampler2D _Particles; uniform float4 _Particles_ST;
            uniform float _Offset;
            struct VertexInput {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
                float2 texcoord0 : TEXCOORD0;
            };
            struct VertexOutput {
                V2F_SHADOW_CASTER;
                float2 uv0 : TEXCOORD1;
                float3 normalDir : TEXCOORD2;
            };
            VertexOutput vert (VertexInput v) {
                VertexOutput o = (VertexOutput)0;
                o.uv0 = v.texcoord0;
                o.normalDir = UnityObjectToWorldNormal(v.normal);
                float4 node_2764 = _Time;
                float node_3690 = (node_2764.r*_node_9008);
                float node_2078 = ((0.1*node_3690)+(sin((node_3690*4.0))*0.2));
                float node_2728 = ((node_3690*0.1)+(sin((node_3690*4.0))*0.2));
                float2 node_3488 = (o.uv0+float2(node_2078,node_2728));
                float4 node_9788 = tex2Dlod(_Particles,float4(TRANSFORM_TEX(node_3488, _Particles),0.0,0));
                v.vertex.xyz += (v.normal*_Offset*(0.5-(1.0 - dot(node_9788.rgb,float3(0.3,0.59,0.11)))));
                o.pos = UnityObjectToClipPos( v.vertex );
                TRANSFER_SHADOW_CASTER(o)
                return o;
            }
            float4 frag(VertexOutput i) : COLOR {
                i.normalDir = normalize(i.normalDir);
                float3 normalDirection = i.normalDir;
                SHADOW_CASTER_FRAGMENT(i)
            }
            ENDCG
        }
    }
    FallBack "Diffuse"
    CustomEditor "ShaderForgeMaterialInspector"
}
