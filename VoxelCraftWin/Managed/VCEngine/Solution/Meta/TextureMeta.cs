using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// JSON Serializable class used as a single instance of a single texture
    /// loaded into the project.
    /// </summary>
    public class TextureMeta
    {
        public int Version = 1;
        public Guid GUID = Guid.NewGuid();
        public String RelativePath;

        [JsonIgnore]
        public Texture GLTexture;

        [OnDeserialized]
        private void OnDeserialized(StreamingContext context)
        {
            try
            {
                String fullpath = PathUtilities.Combine(Project.ActiveProjectDirectory, RelativePath);
                GLTexture = Texture.Get(fullpath, Resources.LoadType.AsyncLowPriority);
            }
            catch (Exception ex)
            {
                Log.Error("Exception during DeSerialization of TextureMeta: " + ex.Message, "JSON");
            }
        }
    }
}
