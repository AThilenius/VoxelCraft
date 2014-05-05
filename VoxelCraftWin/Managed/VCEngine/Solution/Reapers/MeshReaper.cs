using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MeshReaper : FileReaper
    {

        public MeshReaper()
            : base(PathUtilities.MeshExtensions)
        {
        }

        protected override void ReapNew(String fullPath, String relativePath)
        {
            // Load the GL Shader, create a ShaderMeta for it and add it to the project
            Mesh[] meshes = Mesh.Get(fullPath, Resources.LoadType.Immediate);
            MeshMeta meshMeta = new MeshMeta { Name = relativePath, RelativePath = relativePath, Meshes = meshes };
            Project.ActiveProject.Resources.Meshes.Add(meshMeta.GUID, fullPath, meshMeta);
        }

        protected override void ReapChange(String fullPath)
        {
            // Not yet supported
        }

        protected override bool Contains(String fullPath)
        {
            return Project.ActiveProject.Resources.Meshes.ContainsKey(fullPath);
        }

    }
}
