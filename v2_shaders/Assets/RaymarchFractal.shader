Shader "Unlit/RaymarchFractal"
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

            static const int ITERATIONS = 16;
            static const int ESCAPE_RADIUS = 256;

            static const int ALIAS = 2;
            static const int ALIAS2 = ALIAS*ALIAS;
            static const float DIV_ALIAS = 1. / ALIAS;

            float2 comp_mul(float2 a, float2 b)
            {
                return float2(
                    a.x*b.x - a.y*b.y,
                    a.x*b.y + a.y*b.x
                );
            }

            float4 rotate(float4 q, float3 rot)
            {
                // rotate quaternion depending on the camera rotations
                // input quaternion should be normalized and have its w component to 0
                
                float c0 = cos(rot[0]), s0 = sin(rot[0]);
                float c1 = cos(rot[1]), s1 = sin(rot[1]);
                float c2 = cos(rot[2]), s2 = sin(rot[2]);

                float z = q.z;
                q.z = z * c0;
                q.w = z * s0;

                float y = q.y;
                z = q.z;
                q.y = y * c1 - z * s1;
                q.z = z * c1 + y * s1;

                float x = q.x;
                z = q.z;
                q.x = x * c2 + z * s2;
                q.z = z * c2 - x * s2;

                return q;
            }

            float hypersphere_sdf(float4 q)
            {
                float d = dot(q, q) - 2;
                return clamp(d, 0, 1);
            }

            float julia_sdf(float4 q)
            {
                float2 c = q.xy, z = q.zw;

                // init crop
                float zreal = 0;
                if (z.x > 0)
                {
                    zreal = z.x;
                    z.x = 0;
                }

                float2 dz = float2(1, 0);
                float r = 0;

                for (int n = 0; n < ITERATIONS; n++)
                {
                    r = dot(z, z);
                    if (r > ESCAPE_RADIUS) break;

                    dz = comp_mul(dz, z) * 2 + 1;
                    z = comp_mul(z, z) + c;
                }

                // handle crop
                if (r < 2 && zreal) return zreal;
                if (r < 2) return 0;

                // compute modules
                float mz = sqrt(r);
                float mdz = sqrt(dot(dz, dz));
                float d = mz * log(mz) / mdz;

                if (zreal) return sqrt(d * d + zreal * zreal);
                return clamp(d, 0, 1);
            }
            
            float4 getRay(float2 screen_pos, float3 rot)
            {
                float4 dir = float4(
                    screen_pos.x - _ScreenParams.x*.5,
                    screen_pos.y - _ScreenParams.y*.5,
                    -D,
                    0
                );

                return normalize(rotate(dir, rot));
            }

            float dist2(float4 a, float4 b)
            {
                float dx = a.x-b.x, dy = a.y-b.y, dz = a.z-b.y, dw = a.w-b.w;

                return dx*dx + dy*dy + dz*dz + dw*dw;
            }

            // returns float2(
            //     min distance, or >= 0 if hit the object ,
            //     number of steps
            // )
            float2 getRayInfo(float4 cam_pos, float4 ray)
            {
                float4 pos = cam_pos;
                float dist = julia_sdf(pos);
                float minDist = dist;

                int steps = 0;
                while (true)
                {
                    float camDist = dist2(pos, cam_pos);
                    if (camDist > MAXDIST2) break;

                    dist = julia_sdf(pos);
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

            fixed4 postpro(float min_dist, int steps)
            {
                bool hit = min_dist <= 0;
                float color;

                if (hit)
                {
                    // ambient occlusion
                    color = 1/exp(.05 * steps);
                }
                else
                {
                    // glow
                    color = .1 * 1 / (1+min_dist);
                }
                
                return fixed4(color, color, color, 0);
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
                float t = _Time.y;
                
                float4 cam_pos = float4(sin(t)+3, 3, 10, 0);
                float3 cam_rot = float3(0, -0.3, -0.1);
                cam_pos = float4(0, 0, sin(t)*2+5, 0);
                cam_rot = float3(0, 0, 0);

                // handle antialiasing
                float2 info;
                
                for (int i = 0; i < ALIAS2; i++)
                {
                    float4 pos = input.vertex + float4(i%ALIAS * DIV_ALIAS, i/ALIAS * DIV_ALIAS, 0, 0);
                    info += getRayInfo(cam_pos, getRay(pos, cam_rot));
                }

                info *= DIV_ALIAS;

                return postpro(info.x, (int)info.y);
            }
            ENDCG
        }
    }
}
