using TMPro;
using UnityEngine;

public class JuliaSet : MonoBehaviour
{
    public ComputeShader computeShader;
    public Material material;
    public TMP_Text text;
    public Movement movement;

    public Color col;
    public Color bgCol0;
    public Color bgCol1;
    public Color fogCol;

    private RenderTexture _texture;

    private int _kernelHandle;
    private int _threadGroupsX, _threadGroupsY;

    private void Start()
    {
        int w = Screen.width, h = Screen.height;
        
        // set up texture and material
        _texture = new RenderTexture(w, h, 0)
        {
            enableRandomWrite = true
        };
        _texture.Create();

        _kernelHandle = computeShader.FindKernel("CSMain");

        computeShader.SetTexture(_kernelHandle, Cache.Result, _texture);
        computeShader.SetVector(Cache.ScreenSize, new Vector4(w, h, 0, 0));

        _threadGroupsX = Mathf.CeilToInt(w / 8f);
        _threadGroupsY = Mathf.CeilToInt(h / 8f);
        
        material.SetTexture(Cache.MainTex, _texture);
    }
    
    private void OnRenderObject()
    {
        Matrix4x4 camMatrix = movement.Rotation;

        computeShader.SetFloat(Cache.Time, Time.time);
        computeShader.SetFloat(Cache.Step, movement.Step);
        computeShader.SetFloat(Cache.FogDist, movement.FogDist);
        computeShader.SetFloat(Cache.FogDepth, movement.FogDepth);
        computeShader.SetVector(Cache.CamPos, movement.Position);
        computeShader.SetVector(Cache.CamRot0, camMatrix.GetRow(0));
        computeShader.SetVector(Cache.CamRot1, camMatrix.GetRow(1));
        computeShader.SetVector(Cache.CamRot2, camMatrix.GetRow(2));
        computeShader.SetVector(Cache.CamRot3, camMatrix.GetRow(3));
        computeShader.SetVector(Cache.Col, col);
        computeShader.SetVector(Cache.BgCol0, bgCol0);
        computeShader.SetVector(Cache.BgCol1, bgCol1);
        computeShader.SetVector(Cache.FogCol, fogCol);
        computeShader.SetInt(Cache.Alias, movement.Alias);
        
        computeShader.Dispatch(_kernelHandle, _threadGroupsX, _threadGroupsY, 1);
        
        UpdateText(camMatrix);
    }

    private void UpdateText(Matrix4x4 camMatrix)
    {
        if (!movement.ShowMenu)
        {
            text.text = "";
            return;
        }
        
        text.text = $"Position:\n{Print.Vec4(movement.Position)}\nRotation:\n{Print.Mat(camMatrix)}";
        text.text += $"\nAlias: {movement.Alias}\nRaymarch step: {movement.Step}";
        text.text += $"\nFog distance: {movement.FogDist}\nFog depth: {movement.FogDepth}";
        text.text += "\n(Toggle this: Enter)";
    }
}
