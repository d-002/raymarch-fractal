using System;
using UnityEngine;

public static class Print
{
    private const String Format = "F5";
    
    public static String Vec4(Vector4 vector)
    {
        String s = "[ ";
        
        for (int i = 0; i < 4; i++)
        {
            if (i != 0) s += ", ";
            s += vector[i].ToString(Format);
        }

        return s + " ]";
    }
    
    public static String Mat(Matrix4x4 matrix)
    {
        String s = "";

        for (int y = 0; y < 4; y++)
        {
            s += "[ ";
            for (int x = 0; x < 4; x++)
            {
                if (x != 0) s += ", ";
                s += matrix[y * 4 + x].ToString(Format);
            }

            s += " ]\n";
        }

        return s;
    }
}