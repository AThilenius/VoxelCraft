using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace VCEngine
{
    public class ShaderMeta
    {
        public int Version = 1;
        public String Name = "UnNamed";
        public Guid GUID = Guid.NewGuid();
        public String RelativePath;

        [JsonIgnore]
        public Shader GLShader;

        [OnDeserialized]
        private void OnDeserialized(StreamingContext context)
        {
            try
            {
                String fullpath = PathUtilities.Combine(Project.ActiveProjectDirectory, RelativePath);
                GLShader = Shader.GetByPath(fullpath);
            }
            catch (Exception ex)
            {
                Log.Error("Exception during DeSerialization of ShaderMeta: " + ex.Message, "JSON");
            }
        }
    }
}
