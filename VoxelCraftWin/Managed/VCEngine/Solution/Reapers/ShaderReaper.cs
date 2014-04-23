using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// Reaps new, changed, or deleted *.vcshader files from the parent project's path
    /// and handles recompilation of the HLSL code.
    /// </summary>
    public class ShaderReaper : FileReaper
    {
        public ShaderReaper()
            : base(new string[] {"vcshader"})
        {

        }

        protected override void ReapNew(String fullPath, String relativePath)
        {
            // Load the GL Shader, create a ShaderMeta for it and add it to the project
            Shader shader = Shader.GetByPath(fullPath);
            ShaderMeta shaderMeta = new ShaderMeta { Name = shader.Name, RelativePath = relativePath, GLShader = shader };
            Project.ActiveProject.Resources.Shaders.Add(shaderMeta.GUID, fullPath, shaderMeta);
        }

        protected override void ReapChange(String fullPath)
        {
            Shader.GetByPath(fullPath).ReCompileGLSL();
        }

        protected override bool Contains(String fullPath)
        {
            return Project.ActiveProject.Resources.Shaders.ContainsKey(fullPath);
        }
    }
}
