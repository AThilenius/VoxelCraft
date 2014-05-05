using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace VCEngine
{
    public class MeshMeta
    {
        public int Version = 1;
        public String Name = "UnNamed";
        public Guid GUID = Guid.NewGuid();
        public String RelativePath;

        [JsonIgnore]
        public Mesh[] Meshes;

        [OnDeserialized]
        private void OnDeserialized(StreamingContext context)
        {
            try
            {
                String fullpath = PathUtilities.Combine(Project.ActiveProjectDirectory, RelativePath);
                Meshes = Mesh.Get(fullpath, Resources.LoadType.Immediate);
            }
            catch (Exception ex)
            {
                Log.Error("Exception during DeSerialization of MeshMeta: " + ex.Message, "JSON");
            }
        }
    }
}
