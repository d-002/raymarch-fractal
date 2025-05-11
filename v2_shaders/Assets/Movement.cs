using System;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour
{
    private const float MoveSpeed = 0.8f, RotSpeed = 1, FogDistSpeed = 3, FogDepthSpeed = 1;

    private static readonly Dictionary<MoveTypes, KeyCode> MoveKeys = new()
    {
        { MoveTypes.Left, KeyCode.A },
        { MoveTypes.Right, KeyCode.D },
        { MoveTypes.Forwards, KeyCode.W },
        { MoveTypes.Backwards, KeyCode.S },
        { MoveTypes.Up, KeyCode.Space },
        { MoveTypes.Down, KeyCode.LeftShift },
        { MoveTypes.Ana, KeyCode.Q },
        { MoveTypes.Kata, KeyCode.E }
    };

    private static readonly Dictionary<RotTypes, KeyCode> RotKeys = new()
    {
        { RotTypes.XYMinus, KeyCode.H },
        { RotTypes.XYPlus, KeyCode.L },
        { RotTypes.XZMinus, KeyCode.RightArrow },
        { RotTypes.XZPlus, KeyCode.LeftArrow },
        { RotTypes.XWMinus, KeyCode.J },
        { RotTypes.XWPlus, KeyCode.K },
        { RotTypes.YZMinus, KeyCode.UpArrow },
        { RotTypes.YZPlus, KeyCode.DownArrow },
        { RotTypes.YWMinus, KeyCode.Y },
        { RotTypes.YWPlus, KeyCode.O },
        { RotTypes.ZWMinus, KeyCode.U },
        { RotTypes.ZWPlus, KeyCode.I }
    };

    private const KeyCode AliasKey = KeyCode.T;
    private const KeyCode StepKey = KeyCode.G;
    private const KeyCode FogDistPlus = KeyCode.KeypadPlus;
    private const KeyCode FogDistMinus = KeyCode.KeypadMinus;
    private const KeyCode FogDepthPlus = KeyCode.KeypadMultiply;
    private const KeyCode FogDepthMinus = KeyCode.KeypadDivide;
    private const KeyCode ToggleMenu = KeyCode.Return;

    private readonly float[] _rot = {0, -0.61f, 0, 0.35f, 0, 0};
    
    [NonSerialized] public Vector4 Position = new(-2.5f, 1.25f, 1.5f, 0);
    [NonSerialized] public Matrix4x4 Rotation;

    private readonly int[] _aliases = { 1, 2, 4 };
    private int _aliasIndex;
    private readonly float[] _steps = { 1, .8f, .5f, .3f };
    private int _stepIndex;
    
    [NonSerialized] public int Alias;
    [NonSerialized] public float Step;

    [NonSerialized] public float FogDist = 4;
    [NonSerialized] public float FogDepth = .5f;

    [NonSerialized] public bool ShowMenu = true;

    private void UpdateRotation()
    {
        Vector3 cosA = new Vector3(Mathf.Cos(_rot[0]), Mathf.Cos(_rot[1]), Mathf.Cos(_rot[2]));
        Vector3 cosB = new Vector3(Mathf.Cos(_rot[3]), Mathf.Cos(_rot[4]), Mathf.Cos(_rot[5]));
        Vector3 sinA = new Vector3(Mathf.Sin(_rot[0]), Mathf.Sin(_rot[1]), Mathf.Sin(_rot[2]));
        Vector3 sinB = new Vector3(Mathf.Sin(_rot[3]), Mathf.Sin(_rot[4]), Mathf.Sin(_rot[5]));

        Matrix4x4 xyzw = new Matrix4x4(
            new Vector4(cosA.x, -sinA.x, 0, 0),
            new Vector4(sinA.x, cosA.x, 0, 0),
            new Vector4(0, 0, cosB.z, -sinB.z),
            new Vector4(0, 0, sinB.z, cosB.z)
        );
        Matrix4x4 xzyw = new Matrix4x4(
            new Vector4(cosA.y, 0, -sinA.y, 0),
            new Vector4(0, cosB.y, 0, -sinB.y),
            new Vector4(sinA.y, 0, cosA.y, 0),
            new Vector4(0, sinB.y, 0, cosB.y)
        );
        Matrix4x4 xwyz = new Matrix4x4(
            new Vector4(cosA.z, 0, 0, -sinA.z),
            new Vector4(0, cosB.x, -sinB.x, 0),
            new Vector4(0, sinB.x, cosB.x, 0),
            new Vector4(sinA.z, 0, 0, cosA.z)
        );

        Rotation = xyzw * xzyw * xwyz;
    }

    private void AddRotation(float[] acc, float[] add)
    {
        for (int i = 0; i < 6; i++) acc[i] += add[i];
    }

    private void Start()
    {
        Alias = _aliases[_aliasIndex];
        Step = _steps[_stepIndex];
        UpdateRotation();
    }

    private void Update()
    {
        float dt = Mathf.Min(Time.deltaTime, 0.1f);
        float moveSpeed = MoveSpeed * dt;
        float rotSpeed = RotSpeed * dt;
        float fogDistSpeed = FogDistSpeed * dt;
        float fogDepthSpeed = FogDepthSpeed * dt;
        
        // movement
        Vector4 movement = Vector4.zero;

        if (Input.GetKey(MoveKeys[MoveTypes.Left])) movement.x -= moveSpeed;
        if (Input.GetKey(MoveKeys[MoveTypes.Right])) movement.x += moveSpeed;
        if (Input.GetKey(MoveKeys[MoveTypes.Up])) movement.y += moveSpeed;
        if (Input.GetKey(MoveKeys[MoveTypes.Down])) movement.y -= moveSpeed;
        if (Input.GetKey(MoveKeys[MoveTypes.Forwards])) movement.z -= moveSpeed;
        if (Input.GetKey(MoveKeys[MoveTypes.Backwards])) movement.z += moveSpeed;
        if (Input.GetKey(MoveKeys[MoveTypes.Ana])) movement.w -= moveSpeed;
        if (Input.GetKey(MoveKeys[MoveTypes.Kata])) movement.w += moveSpeed;

        Position += Rotation * movement;
        
        // rotation
        float[] rot = new float[6];
        if (Input.GetKey(RotKeys[RotTypes.XYMinus])) rot[0] -= rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.XYPlus])) rot[0] += rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.XZMinus])) rot[1] -= rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.XZPlus])) rot[1] += rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.XWMinus])) rot[2] -= rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.XWPlus])) rot[2] += rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.YZMinus])) rot[3] -= rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.YZPlus])) rot[3] += rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.YWMinus])) rot[4] -= rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.YWPlus])) rot[4] += rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.ZWMinus])) rot[5] -= rotSpeed;
        if (Input.GetKey(RotKeys[RotTypes.ZWPlus])) rot[5] += rotSpeed;
        
        // fog
        if (Input.GetKey(FogDistMinus)) FogDist -= fogDistSpeed;
        if (Input.GetKey(FogDistPlus)) FogDist += fogDistSpeed;
        if (Input.GetKey(FogDepthMinus)) FogDepth -= fogDepthSpeed;
        if (Input.GetKey(FogDepthPlus)) FogDepth += fogDepthSpeed;
        
        // antialiasing
        if (Input.GetKeyDown(AliasKey))
        {
            _aliasIndex = (_aliasIndex + 1) % _aliases.Length;
            Alias = _aliases[_aliasIndex];
        }
        
        // raymarch steps size
        if (Input.GetKeyDown(StepKey))
        {
            _stepIndex = (_stepIndex + 1) % _steps.Length;
            Step = _steps[_stepIndex];
        }
        
        // menu
        if (Input.GetKeyDown(ToggleMenu)) ShowMenu = !ShowMenu;

        AddRotation(_rot, rot);
        UpdateRotation();
    }
}
