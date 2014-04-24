using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TextureReaper : FileReaper
    {
        public TextureReaper()
            : base(PathUtilities.TextureExtensions)
        {
        }

        protected override void ReapNew(String fullPath, String relativePath)
        {
            // Load the GL Shader, create a ShaderMeta for it and add it to the project
            Texture texture = Texture.Get(fullPath, Resources.LoadType.AsyncLowPriority);

            TextureMeta textureMeta = new TextureMeta { RelativePath = relativePath, GLTexture = texture };
            Project.ActiveProject.Resources.Textures.Add(textureMeta.GUID, fullPath, textureMeta);
        }

        protected override void ReapChange(String fullPath)
        {
            Texture.Reload(fullPath, Resources.LoadType.AsyncLowPriority);
        }

        protected override bool Contains(String fullPath)
        {
            return Project.ActiveProject.Resources.Textures.ContainsKey(fullPath);
        }
    }
}
