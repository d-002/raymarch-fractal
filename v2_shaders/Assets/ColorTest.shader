Shader "Unlit/ColorTest"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            // make fog work
            #pragma multi_compile_fog

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                UNITY_FOG_COORDS(1)
                float4 vertex : SV_POSITION;
            };

            sampler2D _MainTex;
            float4 _MainTex_ST;

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                return o;
            }

            fixed4 frag (v2f input) : SV_Target
            {
                float x = input.vertex.x*2 - _ScreenParams.x, y = input.vertex.y*2 - _ScreenParams.y;
                float z = _Time.y, w = _Time.z;

                fixed4 red = fixed4(1, .3, .3, 1);
                fixed4 green = fixed4(.3, 1, .3, 1);
                fixed4 blue = fixed4(.3, .3, 1, 1);

                float angle = atan2(y, x);
                float dist = sqrt(x*x + y*y)/_ScreenParams.y;

                int value = sin(angle*10) < cos(dist*cos(z));
                //value += sin(x/_ScreenParams.y) < sin(y/_ScreenParams.y);
                value += (sin(dist*10 + angle*cos(z))+1)/2 % 1 < 0.4;

                return value == 0 ? red : value == 1 ? green : blue;
            }
            ENDCG
        }
    }
}
