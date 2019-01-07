// Shader created with Shader Forge v1.38 
// Shader Forge (c) Freya Holmer - http://www.acegikmo.com/shaderforge/
// Note: Manually altering this data may prevent you from opening it in Shader Forge
/*SF_DATA;ver:1.38;sub:START;pass:START;ps:flbk:,iptp:0,cusa:False,bamd:0,cgin:,lico:1,lgpr:1,limd:0,spmd:1,trmd:0,grmd:0,uamb:True,mssp:True,bkdf:False,hqlp:False,rprd:False,enco:False,rmgx:True,imps:True,rpth:0,vtps:0,hqsc:True,nrmq:1,nrsp:0,vomd:0,spxs:False,tesm:0,olmd:1,culm:2,bsrc:0,bdst:0,dpts:6,wrdp:False,dith:0,atcv:False,rfrpo:True,rfrpn:Refraction,coma:15,ufog:True,aust:False,igpj:True,qofs:0,qpre:3,rntp:2,fgom:False,fgoc:True,fgod:False,fgor:False,fgmd:0,fgcr:0,fgcg:0,fgcb:0,fgca:1,fgde:0.01,fgrn:0,fgrf:300,stcl:False,atwp:False,stva:128,stmr:255,stmw:255,stcp:6,stps:0,stfa:0,stfz:0,ofsf:0,ofsu:0,f2p0:False,fnsp:True,fnfb:True,fsmp:False;n:type:ShaderForge.SFN_Final,id:4795,x:33397,y:32659,varname:node_4795,prsc:2|emission-7868-OUT,voffset-6422-OUT;n:type:ShaderForge.SFN_Multiply,id:2393,x:32998,y:32682,varname:node_2393,prsc:2|A-9162-OUT,B-382-RGB,C-797-RGB,D-9248-OUT;n:type:ShaderForge.SFN_Color,id:797,x:32322,y:32761,ptovrint:True,ptlb:Color,ptin:_TintColor,varname:_TintColor,prsc:2,glob:False,taghide:False,taghdr:True,tagprd:False,tagnsco:False,tagnrm:False,c1:0.5,c2:0.5,c3:0.5,c4:1;n:type:ShaderForge.SFN_Vector1,id:9248,x:32240,y:32921,varname:node_9248,prsc:2,v1:2;n:type:ShaderForge.SFN_Append,id:4385,x:31716,y:32577,varname:node_4385,prsc:2|A-4550-OUT,B-8550-OUT;n:type:ShaderForge.SFN_Time,id:4645,x:31193,y:32436,varname:node_4645,prsc:2;n:type:ShaderForge.SFN_ValueProperty,id:5965,x:31208,y:32652,ptovrint:False,ptlb:ScrollSpeed1,ptin:_ScrollSpeed1,varname:node_5965,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,v1:1;n:type:ShaderForge.SFN_Multiply,id:4550,x:31404,y:32562,varname:node_4550,prsc:2|A-4645-T,B-5965-OUT;n:type:ShaderForge.SFN_Vector1,id:8550,x:31523,y:32611,varname:node_8550,prsc:2,v1:0;n:type:ShaderForge.SFN_Add,id:7871,x:31955,y:32497,varname:node_7871,prsc:2|A-6691-UVOUT,B-4385-OUT;n:type:ShaderForge.SFN_TexCoord,id:6691,x:31716,y:32430,varname:node_6691,prsc:2,uv:0,uaff:False;n:type:ShaderForge.SFN_Time,id:9790,x:31042,y:33000,varname:node_9790,prsc:2;n:type:ShaderForge.SFN_Multiply,id:1404,x:31377,y:33150,varname:node_1404,prsc:2|A-9790-T,B-5239-OUT;n:type:ShaderForge.SFN_Append,id:4410,x:31689,y:33165,varname:node_4410,prsc:2|A-1404-OUT,B-4863-OUT;n:type:ShaderForge.SFN_TexCoord,id:4460,x:31579,y:32986,varname:node_4460,prsc:2,uv:1,uaff:False;n:type:ShaderForge.SFN_Add,id:5464,x:31928,y:33085,varname:node_5464,prsc:2|A-4460-UVOUT,B-4410-OUT;n:type:ShaderForge.SFN_Vector1,id:4863,x:31315,y:33377,varname:node_4863,prsc:2,v1:0;n:type:ShaderForge.SFN_Multiply,id:3522,x:31404,y:32690,varname:node_3522,prsc:2|A-4645-T,B-5965-OUT,C-1289-OUT;n:type:ShaderForge.SFN_Vector1,id:1289,x:31208,y:32740,varname:node_1289,prsc:2,v1:-0.43;n:type:ShaderForge.SFN_Append,id:7169,x:31716,y:32709,varname:node_7169,prsc:2|A-3522-OUT,B-8550-OUT;n:type:ShaderForge.SFN_Tex2d,id:6979,x:32235,y:32559,varname:node_6979,prsc:2,ntxv:0,isnm:False|UVIN-6836-OUT,TEX-9610-TEX;n:type:ShaderForge.SFN_Tex2d,id:7521,x:32235,y:32413,varname:node_7521,prsc:2,ntxv:0,isnm:False|UVIN-7871-OUT,TEX-9610-TEX;n:type:ShaderForge.SFN_Tex2dAsset,id:9610,x:31983,y:32192,ptovrint:False,ptlb:Main,ptin:_Main,varname:node_9610,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,ntxv:0,isnm:False;n:type:ShaderForge.SFN_Add,id:6836,x:31972,y:32668,varname:node_6836,prsc:2|A-6691-UVOUT,B-7169-OUT;n:type:ShaderForge.SFN_Add,id:9162,x:32446,y:32487,varname:node_9162,prsc:2|A-7521-RGB,B-6979-RGB;n:type:ShaderForge.SFN_Tex2dAsset,id:4251,x:31714,y:33492,ptovrint:False,ptlb:Ramp,ptin:_Ramp,varname:node_4251,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,ntxv:0,isnm:False;n:type:ShaderForge.SFN_Tex2d,id:9942,x:32049,y:33268,varname:node_9942,prsc:2,ntxv:0,isnm:False|UVIN-5464-OUT,TEX-4251-TEX;n:type:ShaderForge.SFN_Desaturate,id:4209,x:32247,y:33268,varname:node_4209,prsc:2|COL-9942-RGB;n:type:ShaderForge.SFN_NormalVector,id:5130,x:32664,y:33354,prsc:2,pt:False;n:type:ShaderForge.SFN_Multiply,id:6422,x:32566,y:33194,varname:node_6422,prsc:2|A-4209-OUT,B-5130-OUT,C-7679-OUT;n:type:ShaderForge.SFN_ValueProperty,id:7679,x:32222,y:33468,ptovrint:False,ptlb:NormalPush,ptin:_NormalPush,varname:node_7679,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,v1:0;n:type:ShaderForge.SFN_ValueProperty,id:5239,x:31003,y:33285,ptovrint:False,ptlb:PulseSpeed,ptin:_PulseSpeed,varname:node_5239,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,v1:0;n:type:ShaderForge.SFN_Add,id:4711,x:32467,y:33074,varname:node_4711,prsc:2|A-4209-OUT,B-3486-OUT;n:type:ShaderForge.SFN_Vector1,id:3486,x:32203,y:33194,varname:node_3486,prsc:2,v1:0;n:type:ShaderForge.SFN_Tex2dAsset,id:9821,x:32357,y:31988,ptovrint:False,ptlb:ColorRamp,ptin:_ColorRamp,varname:node_9821,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,ntxv:0,isnm:False;n:type:ShaderForge.SFN_Tex2d,id:382,x:32942,y:32063,varname:node_382,prsc:2,ntxv:0,isnm:False|UVIN-3274-UVOUT,TEX-9821-TEX;n:type:ShaderForge.SFN_Panner,id:3274,x:33033,y:31532,varname:node_3274,prsc:2,spu:1,spv:0|UVIN-8904-OUT,DIST-4340-OUT;n:type:ShaderForge.SFN_VertexColor,id:2856,x:32438,y:31451,varname:node_2856,prsc:2;n:type:ShaderForge.SFN_Append,id:8904,x:32685,y:31534,varname:node_8904,prsc:2|A-2856-R,B-4002-OUT;n:type:ShaderForge.SFN_Vector1,id:4002,x:32438,y:31585,varname:node_4002,prsc:2,v1:0;n:type:ShaderForge.SFN_ValueProperty,id:933,x:32286,y:31801,ptovrint:False,ptlb:ColorShift,ptin:_ColorShift,varname:node_933,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,v1:1;n:type:ShaderForge.SFN_Multiply,id:4340,x:32557,y:31764,varname:node_4340,prsc:2|A-2309-T,B-933-OUT;n:type:ShaderForge.SFN_Time,id:2309,x:32195,y:31613,varname:node_2309,prsc:2;n:type:ShaderForge.SFN_Multiply,id:6723,x:32775,y:32918,varname:node_6723,prsc:2|A-561-OUT,B-4711-OUT,C-382-RGB,D-806-OUT;n:type:ShaderForge.SFN_ValueProperty,id:561,x:32287,y:33051,ptovrint:False,ptlb:PulseEffect,ptin:_PulseEffect,varname:node_561,prsc:2,glob:False,taghide:False,taghdr:False,tagprd:False,tagnsco:False,tagnrm:False,v1:1;n:type:ShaderForge.SFN_Add,id:7868,x:33122,y:32824,varname:node_7868,prsc:2|A-2393-OUT,B-6723-OUT;n:type:ShaderForge.SFN_Desaturate,id:806,x:32606,y:32729,varname:node_806,prsc:2|COL-9162-OUT;proporder:797-5965-9610-4251-7679-5239-9821-933-561;pass:END;sub:END;*/

Shader "Shader Forge/Veins" {
    Properties {
        [HDR]_TintColor ("Color", Color) = (0.5,0.5,0.5,1)
        _ScrollSpeed1 ("ScrollSpeed1", Float ) = 1
        _Main ("Main", 2D) = "white" {}
        _Ramp ("Ramp", 2D) = "white" {}
        _NormalPush ("NormalPush", Float ) = 0
        _PulseSpeed ("PulseSpeed", Float ) = 0
        _ColorRamp ("ColorRamp", 2D) = "white" {}
        _ColorShift ("ColorShift", Float ) = 1
        _PulseEffect ("PulseEffect", Float ) = 1
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
            Cull Off
            ZTest Always
            ZWrite Off
            
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"
            #pragma multi_compile_fwdbase
            #pragma multi_compile_fog
            #pragma only_renderers d3d9 d3d11 glcore gles gles3 metal 
            #pragma target 3.0
            uniform float4 _TintColor;
            uniform float _ScrollSpeed1;
            uniform sampler2D _Main; uniform float4 _Main_ST;
            uniform sampler2D _Ramp; uniform float4 _Ramp_ST;
            uniform float _NormalPush;
            uniform float _PulseSpeed;
            uniform sampler2D _ColorRamp; uniform float4 _ColorRamp_ST;
            uniform float _ColorShift;
            uniform float _PulseEffect;
            struct VertexInput {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
                float2 texcoord0 : TEXCOORD0;
                float2 texcoord1 : TEXCOORD1;
                float4 vertexColor : COLOR;
            };
            struct VertexOutput {
                float4 pos : SV_POSITION;
                float2 uv0 : TEXCOORD0;
                float2 uv1 : TEXCOORD1;
                float4 posWorld : TEXCOORD2;
                float3 normalDir : TEXCOORD3;
                float4 vertexColor : COLOR;
                UNITY_FOG_COORDS(4)
            };
            VertexOutput vert (VertexInput v) {
                VertexOutput o = (VertexOutput)0;
                o.uv0 = v.texcoord0;
                o.uv1 = v.texcoord1;
                o.vertexColor = v.vertexColor;
                o.normalDir = UnityObjectToWorldNormal(v.normal);
                float4 node_9790 = _Time;
                float2 node_5464 = (o.uv1+float2((node_9790.g*_PulseSpeed),0.0));
                float4 node_9942 = tex2Dlod(_Ramp,float4(TRANSFORM_TEX(node_5464, _Ramp),0.0,0));
                float node_4209 = dot(node_9942.rgb,float3(0.3,0.59,0.11));
                v.vertex.xyz += (node_4209*v.normal*_NormalPush);
                o.posWorld = mul(unity_ObjectToWorld, v.vertex);
                o.pos = UnityObjectToClipPos( v.vertex );
                UNITY_TRANSFER_FOG(o,o.pos);
                return o;
            }
            float4 frag(VertexOutput i, float facing : VFACE) : COLOR {
                float isFrontFace = ( facing >= 0 ? 1 : 0 );
                float faceSign = ( facing >= 0 ? 1 : -1 );
                i.normalDir = normalize(i.normalDir);
                i.normalDir *= faceSign;
                float3 viewDirection = normalize(_WorldSpaceCameraPos.xyz - i.posWorld.xyz);
                float3 normalDirection = i.normalDir;
////// Lighting:
////// Emissive:
                float4 node_4645 = _Time;
                float node_8550 = 0.0;
                float2 node_7871 = (i.uv0+float2((node_4645.g*_ScrollSpeed1),node_8550));
                float4 node_7521 = tex2D(_Main,TRANSFORM_TEX(node_7871, _Main));
                float2 node_6836 = (i.uv0+float2((node_4645.g*_ScrollSpeed1*(-0.43)),node_8550));
                float4 node_6979 = tex2D(_Main,TRANSFORM_TEX(node_6836, _Main));
                float3 node_9162 = (node_7521.rgb+node_6979.rgb);
                float4 node_2309 = _Time;
                float2 node_3274 = (float2(i.vertexColor.r,0.0)+(node_2309.g*_ColorShift)*float2(1,0));
                float4 node_382 = tex2D(_ColorRamp,TRANSFORM_TEX(node_3274, _ColorRamp));
                float4 node_9790 = _Time;
                float2 node_5464 = (i.uv1+float2((node_9790.g*_PulseSpeed),0.0));
                float4 node_9942 = tex2D(_Ramp,TRANSFORM_TEX(node_5464, _Ramp));
                float node_4209 = dot(node_9942.rgb,float3(0.3,0.59,0.11));
                float3 emissive = ((node_9162*node_382.rgb*_TintColor.rgb*2.0)+(_PulseEffect*(node_4209+0.0)*node_382.rgb*dot(node_9162,float3(0.3,0.59,0.11))));
                float3 finalColor = emissive;
                fixed4 finalRGBA = fixed4(finalColor,1);
                UNITY_APPLY_FOG_COLOR(i.fogCoord, finalRGBA, fixed4(0,0,0,1));
                return finalRGBA;
            }
            ENDCG
        }
    }
    CustomEditor "ShaderForgeMaterialInspector"
}
