using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EntityDescription
    {
        // Description:
        public Int32 ID;
        public Mesh Mesh;
        public Transform Transform;
        public List<Type> Components;
        public List<EntityDescription> Children;

        /// <summary>
        /// Returns an instance of the described entity(s).
        /// </summary>
        public Entity GetInstance()
        {
            throw new NotImplementedException();
        }

    }
}