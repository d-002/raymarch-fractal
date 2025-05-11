using UnityEngine;

public class FrameLimit : MonoBehaviour
{
    public int framerate;
    
    void Start()
    {
        //#if UNITY_EDITOR
        Application.targetFrameRate = framerate;
        //#endif
    }
}
