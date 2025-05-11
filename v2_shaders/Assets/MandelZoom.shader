Shader "Unlit/MandelZoom"
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

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };
            
            sampler2D _MainTex;
            float4 _MainTex_ST;

            static const float RATIO = _ScreenParams.x/_ScreenParams.y;

            static const float2 TARGET = float2(-.8181282518007618, .1988497155323609);
            static const float FINAL_ZOOM = 5000000;
            static const float ANIM_TIME = 20;

            static const int ALIAS = 2;
            static const int ALIAS2 = ALIAS*ALIAS;
            static const float DIV_ALIAS = 1. / ALIAS;

            float mandel(float2 c, int iterations)
            {
                float2 z = 0;

                for (int i = 0; i < iterations; i++)
                {
                    z = float2(
                        z.x * z.x - z.y * z.y,
                        z.x * z.y + z.y * z.x
                    ) + c;

                    if (dot(z, z) > 4) return (float)i/iterations;
                }

                return 0;
            }

            // real, imag, iterations
            float3 getSettings(float4 screen_pos)
            {
                float2 pos = float2(
                    (screen_pos.x/_ScreenParams.x - .5) * RATIO,
                    screen_pos.y/_ScreenParams.y - .5
                ) * 2;

                float t =_Time.y % ANIM_TIME / ANIM_TIME;
                
                float zoom = pow(FINAL_ZOOM, t);
                pos = pos/zoom + TARGET;

                return float3(pos, 64 + pow(FINAL_ZOOM, .35)*t);
            }

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                
                return o;
            }

            fixed4 frag (v2f input) : SV_Target
            {
                // handle antialiasing
                float t = 0;
                
                for (int i = 0; i < ALIAS2; i++) {
                    float3 settings = getSettings(input.vertex + float4(i%ALIAS * DIV_ALIAS, i/ALIAS * DIV_ALIAS, 0, 0));

                    t += mandel(settings.xy, settings.z);
                }

                t /= ALIAS2;

                fixed4 col;
                if (t < 0) col = fixed4(0, 0, 0, 0);
                else {
                    col = fixed4(t, t, t, 0);
                }
                
                return col;
            }
            ENDCG
        }
    }
}
