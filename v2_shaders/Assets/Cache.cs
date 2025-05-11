using UnityEngine;

public static class Cache
{
    public static readonly int Result = Shader.PropertyToID("Result");
    public static readonly int ScreenSize = Shader.PropertyToID("_ScreenSize");
    public static readonly int MainTex = Shader.PropertyToID("_MainTex");
    
    public static readonly int Time = Shader.PropertyToID("_Time");
    public static readonly int Step = Shader.PropertyToID("_Step");
    
    public static readonly int FogDist = Shader.PropertyToID("_FogDist");
    public static readonly int FogDepth = Shader.PropertyToID("_FogDepth");

    public static readonly int CamPos = Shader.PropertyToID("_CamPos");

    public static readonly int CamRot0 = Shader.PropertyToID("_CamRot0");
    public static readonly int CamRot1 = Shader.PropertyToID("_CamRot1");
    public static readonly int CamRot2 = Shader.PropertyToID("_CamRot2");
    public static readonly int CamRot3 = Shader.PropertyToID("_CamRot3");

    public static readonly int Col = Shader.PropertyToID("_Col");
    public static readonly int BgCol0 = Shader.PropertyToID("_BgCol0");
    public static readonly int BgCol1 = Shader.PropertyToID("_BgCol1");
    public static readonly int FogCol = Shader.PropertyToID("_FogCol");
    
    public static readonly int Alias = Shader.PropertyToID("ALIAS");
}