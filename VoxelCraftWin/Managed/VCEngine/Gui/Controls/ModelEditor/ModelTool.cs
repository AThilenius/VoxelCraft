using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public abstract class ModelTool
    {
        public World World;
        public GameWindow Parent;
        public Boolean Active;

        public ModelTool(GameWindow parent)
        {
            Parent = parent;
            World = parent.World;
        }

        public virtual void Activate()
        {
        }

        public virtual void DeActivate()
        {
        }

        public virtual void Update( RaycastHit? rayHit )
        {
        }
    }
}
