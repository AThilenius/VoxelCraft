using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace VCEngine
{
    public class MaterialMeta
    {
        public int Version = 1;
        public String Name = "UnNamed";
        public Guid GUID = Guid.NewGuid();
        public String RelativePath;

        [JsonIgnore]
        public Material Material;

        [OnDeserialized]
        private void OnDeserialized(StreamingContext context)
        {
            try
            {
                String fullpath = PathUtilities.Combine(Project.ActiveProjectDirectory, RelativePath);
                Material = Material.Get(fullpath);
            }
            catch (Exception ex)
            {
                Log.Error("Exception during DeSerialization of ShaderMeta: " + ex.Message, "JSON");
            }
        }
    }
}
