Shader "ViewBlocker" {
	 Properties {
        _Fade ("Fade", Range(0,1) ) = 1
    }

	CGINCLUDE

		fixed _Fade;

		#include "UnityCG.cginc"
					
		struct v2f {
			half4 pos : SV_POSITION;
            half4 color : Color;
		};

		v2f vert(appdata_full v) {
			v2f o;
			
			o.pos = UnityObjectToClipPos (v.vertex);	
            o.color = v.color;
					
			return o; 
		}
		
		fixed4 frag( v2f i ) : COLOR {	
			//return i.color; 
			return fixed4(0,0,0,i.color.a * _Fade);
		}
	
	ENDCG
	
	SubShader {
		Tags { "RenderType" = "Transparent" "Queue" = "Transparent +100"}
		Lighting Off
		ZWrite Off
		Fog { Mode Off }
		Blend SrcAlpha OneMinusSrcAlpha 
		
	Pass {
	
		CGPROGRAM
		
		#pragma vertex vert
		#pragma fragment frag
		#pragma fragmentoption ARB_precision_hint_fastest 
		
		ENDCG
		 
		}
				
	} 
	FallBack Off 
}