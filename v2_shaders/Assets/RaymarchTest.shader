Shader "Unlit/RaymarchTest"
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
            
            static const float FOV = radians(90);
            static const float D = _ScreenParams.x/2 / atan(FOV/2);
            static const float THRESHOLD = 0.01;
            static const float MAXDIST2 = pow(100, 2);

            static const float3 camPos = float3(0, 0, 10);

            float sdf(float3 pos)
            {
                return length(pos)-2;
            }
            
            float3 getRay(float2 screen_pos)
            {
                float2 centered_pos = float2(
                    screen_pos.x - _ScreenParams.x*.5,
                    screen_pos.y - _ScreenParams.y*.5
                );

                return normalize(float3(centered_pos.x, centered_pos.y, -D));
            }

            float dist2(float3 a, float3 b)
            {
                float dx = a.x-b.x, dy = a.y-b.y, dz = a.z-b.y;

                return dx*dx + dy*dy + dz*dz;
            }

            // returns float2(
            //     min distance, or >= 0 if hit the object ,
            //     number of steps
            // )
            float getRayInfo(float3 pos, float3 ray)
            {
                float dist = sdf(pos);
                float minDist = dist;

                int steps = 0;
                while (true)
                {
                    float camDist = dist2(pos, camPos);
                    if (camDist > MAXDIST2) break;

                    dist = sdf(pos);
                    if (dist < minDist) minDist = dist;

                    if (dist <= THRESHOLD) {
                        minDist = 0;
                        break;
                    }
                    
                    pos += ray*dist;
                    steps++;
                }

                return float2(minDist, steps);
            }

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                float2 info = getRayInfo(camPos, getRay(i.vertex));
                float c = info.x <= 0 ? 1 : 0;
                
                fixed4 col = fixed4(c, c, c, 0);
                
                return col;
            }
            ENDCG
        }
    }
}
