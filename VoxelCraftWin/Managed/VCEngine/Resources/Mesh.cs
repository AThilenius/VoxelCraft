using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class Mesh
    {
        public VCStandardVerticie[] Verticies;
        public int      UsedBufferID;
        public Byte[]   ByteIndexBuffer = null;
        public UInt16[] ShortIndexBuffer = null;
        public UInt32[] IntIndexBuffer = null;

        public GLBuffer Buffer;

        public static Mesh[] Get(String fullPath, Resources.LoadType loadType)
        {
            if (loadType != Resources.LoadType.Immediate)
                throw new NotSupportedException("Only Immediate loading of meshes is currently supported");

            fullPath = Path.GetFullPath(fullPath);
            PathUtilities.TestFileExistance(fullPath);

            int meshCount = 0;

            IntPtr pScene = Assimp.VCIneteropAssimpLoadScene(fullPath,
                Assimp.PostProcessStepsFlags.aiProcess_GenSmoothNormals      |
                Assimp.PostProcessStepsFlags.aiProcess_CalcTangentSpace      |
                Assimp.PostProcessStepsFlags.aiProcess_Triangulate           |
                Assimp.PostProcessStepsFlags.aiProcess_JoinIdenticalVertices |
                Assimp.PostProcessStepsFlags.aiProcess_SortByPType           |
                Assimp.PostProcessStepsFlags.aiProcess_FlipUVs,
                out meshCount);

            Mesh[] meshes = new Mesh[meshCount];

            // For each Mesh in the Model
            for (int meshId = 0; meshId < meshCount; meshId++)
            {
                // Get the mesh info
                int vertCount = 0, facesCount = 0, animMeshesCount = 0, bonesCount = 0;
                Assimp.VCInteropAssimpGetMeshMeta(pScene, meshId, out vertCount, out facesCount, out animMeshesCount, out bonesCount);

                int indexCount = facesCount * 3;

                // Create Index Buffer based on size
                Mesh mesh = new Mesh();
                mesh.Verticies = new VCStandardVerticie[vertCount];
                meshes[meshId] = mesh;

                // Pin the Vertex array
                GCHandle vertsHandle = GCHandle.Alloc(mesh.Verticies, GCHandleType.Pinned);

                // GCHandle for the Index array
                GCHandle indexHandle = new GCHandle();

                // Fits UInt8
                if (indexCount <= (1 << 8))
                {
                    mesh.UsedBufferID = 0;
                    mesh.ByteIndexBuffer = new Byte[indexCount];
                    indexHandle = GCHandle.Alloc(mesh.ByteIndexBuffer, GCHandleType.Pinned);
                    Assimp.VCInteropAssimpGetMeshData(pScene, meshId, vertsHandle.AddrOfPinnedObject(), indexHandle.AddrOfPinnedObject());
                }

                // Fits UInt16
                else if (indexCount <= (1 << 16))
                {
                    mesh.UsedBufferID = 1;
                    mesh.ShortIndexBuffer = new UInt16[indexCount];
                    indexHandle = GCHandle.Alloc(mesh.ShortIndexBuffer, GCHandleType.Pinned);
                    Assimp.VCInteropAssimpGetMeshData(pScene, meshId, vertsHandle.AddrOfPinnedObject(), indexHandle.AddrOfPinnedObject());
                }

                // Fits UInt32
                else if (indexCount <= (1 << 32))
                {
                    mesh.UsedBufferID = 2;
                    mesh.IntIndexBuffer = new UInt32[indexCount];
                    indexHandle = GCHandle.Alloc(mesh.IntIndexBuffer, GCHandleType.Pinned);
                    Assimp.VCInteropAssimpGetMeshData(pScene, meshId, vertsHandle.AddrOfPinnedObject(), indexHandle.AddrOfPinnedObject());
                }

                else
                    Log.Error("WTF happened...", "Resources");

                mesh.Buffer = new GLBuffer();

                // Setup Vertex Attribs, and buffer Vertex Data
                VCStandardVerticie.FillVertexBufferSpecification(mesh.Buffer);
                mesh.Buffer.VertexBufferSpecification(GLDrawPrimitives.Triangles)
		            .SetVertexData((UInt32) (VCStandardVerticie.SizeOf * vertCount), vertsHandle.AddrOfPinnedObject(), vertCount);

                // Buffer Index Data
                if ( mesh.UsedBufferID == 0)
	                mesh.Buffer.IndexBufferSpecification(sizeof(Byte) * indexCount, indexHandle.AddrOfPinnedObject(), indexCount);

                else if (mesh.UsedBufferID == 1)
	                mesh.Buffer.IndexBufferSpecification(sizeof(UInt16) * indexCount, indexHandle.AddrOfPinnedObject(), indexCount);

                else
	                mesh.Buffer.IndexBufferSpecification(sizeof(UInt32) * indexCount, indexHandle.AddrOfPinnedObject(), indexCount);

                // Un-Pin the Vertex and index array
                vertsHandle.Free();
                indexHandle.Free();
            }

            Assimp.VCInteropAssimpFreeScene(pScene);

            return meshes;
        }

    }
}
