Shader "Fasett/Lit with pans"{
    Properties    {
        [NoScaleOffset] _MainTex ("Texture", 2D) = "white" {}
        _Effect ("Effect", 2D) = "white" {}
        [HDR] _EffectTint ("EffectTint", Color) = (1,1,1,1)
        _PanX ("Pan X", float) = 1
        _PanY ("Pan Y", float) = 1
    }
    SubShader    {
        Pass        {
            Tags {"LightMode"="ForwardBase"}
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"
            #include "Lighting.cginc"

            sampler2D _MainTex;
			sampler2D _Effect;
			fixed _PanX;
			fixed _PanY;
			fixed4 _EffectTint;

          // compile shader into multiple variants, with and without shadows
            // (we don't care about any lightmaps yet, so skip these variants)
            #pragma multi_compile_fwdbase nolightmap nodirlightmap nodynlightmap novertexlight
            // shadow helper functions and macros
            #include "AutoLight.cginc"

            struct v2f
            {
                float2 uv : TEXCOORD0;
                SHADOW_COORDS(1) // put shadows data into TEXCOORD1
                fixed3 diff : COLOR0;
                fixed3 ambient : COLOR1;
                fixed4 color : COLOR2;
                float4 pos : SV_POSITION;
            };

            v2f vert (appdata_full v)
            {
                v2f o;
                o.pos = UnityObjectToClipPos(v.vertex);
                o.uv = v.texcoord;
                half3 worldNormal = UnityObjectToWorldNormal(v.normal);
                o.color = v.color;
                half nl = max(0, dot(worldNormal, _WorldSpaceLightPos0.xyz));
                o.diff = nl * _LightColor0.rgb;
                o.ambient = ShadeSH9(half4(worldNormal,1));
                // compute shadows data
                TRANSFER_SHADOW(o)
                return o;
            }


            fixed4 frag (v2f i) : SV_Target
            {
                fixed4 col = tex2D(_MainTex, i.uv);
				fixed2 uv = (i.uv.x + i.color.x + _Time * _PanY, i.uv.y + i.color.y + _Time * _PanX  );
                fixed4 eff = tex2D(_Effect, uv) * _EffectTint;
                // compute shadow attenuation (1.0 = fully lit, 0.0 = fully shadowed)
                fixed shadow = SHADOW_ATTENUATION(i);
                // darken light's illumination with shadow, keep ambient intact
                fixed3 lighting = i.diff * shadow + i.ambient;
                col.rgb *= lighting;
                return col + eff;
            }
            ENDCG
        }

        // shadow casting support
        UsePass "Legacy Shaders/VertexLit/SHADOWCASTER"
    }
}