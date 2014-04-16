using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// JSON Serializable class used as a single instance of a single texture
    /// loaded into the project.
    /// </summary>
    public class TextureMeta
    {
        public String Name = "UnNamed";
        public String RelativePath;

        [JsonIgnore]
        public Texture GLTexture
        {
            get
            {
                //m_glTexture = m_glTexture ?? Texture.GetRelative(RelativePath);
                return m_glTexture;
            }
        }

        [JsonIgnore]
        private Texture m_glTexture;
    }
}
