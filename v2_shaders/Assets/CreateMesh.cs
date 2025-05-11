using System.Collections.Generic;
using UnityEngine;

public class CreateMesh : MonoBehaviour
{
    public int resolution;
    public float size;
    public MeshFilter myMesh;
    
    void Start()
    {
        Vector3 offset = transform.position - new Vector3(size / 2, 0, size / 2);
        
        Mesh mesh = new();
        List<Vector3> vertices = new();
        List<int> triangles = new();
        List<Vector2> uv = new();
        
        // vertices, UV
        float multSize = size / resolution;
        for (int z = 0; z <= resolution; z++)
        for (int x = 0; x <= resolution; x++)
        {
            vertices.Add(new Vector3(x * multSize, 0, z * multSize) + offset);
            uv.Add(new Vector2((float)x / resolution, (float)z / resolution));
        }
        
        // triangles
        for (int z = 0, i = 0; z < resolution; z++)
        for (int x = 0; x < resolution; x++, i++)
        {
            int i2 = i + resolution + 1;
            triangles.AddRange(new[] { i, i2, i + 1, i + 1, i2, i2 + 1 });

            if (x == resolution - 1) i++;
        }

        // mesh
        mesh.vertices = vertices.ToArray();
        mesh.triangles = triangles.ToArray();
        mesh.uv = uv.ToArray();
        mesh.RecalculateNormals();

        myMesh.mesh = mesh;
    }
}
