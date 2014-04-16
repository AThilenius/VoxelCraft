using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// JSON Serializable class that acts as the parent for all resources added to the project.
    /// </summary>
    public class ProjectResources
    {

        public Dictionary<Guid, TextureMeta> Textures = new Dictionary<Guid, TextureMeta>();
        
    }
}
