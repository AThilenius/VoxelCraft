using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MeshMeta
    {
        public int Version = 1;
        public String Name = "UnNamed";
        public Guid GUID = Guid.NewGuid();
        public String RelativePath;
    }
}
