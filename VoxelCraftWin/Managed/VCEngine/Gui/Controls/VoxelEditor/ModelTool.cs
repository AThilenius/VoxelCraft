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
        public Window ParentWindow;

        protected GlfwInputState m_glfwInputState { get { return ParentWindow.GlfwInputState; } }
        protected Input m_input { get { return ParentWindow.Input; } }

        public ModelTool(Window window, GameWindow parent)
        {
            ParentWindow = window;
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
