using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialPreviewer : RenderWindow
    {

        //public ToggleButton PlaneButton;
        //public ToggleButton SphereButton; 

        public String MaterialPath
        {
            get { return m_materialPath; }
            set
            {
                m_materialPath = value;
                GLRenderViewport.Entities.Clear();

                RenderedEntity Plane = new RenderedEntity(Path.Combine(PathUtilities.AssetsPath, @"Models\Plane.obj"), value);
                Plane.Transform.Position = new Vector3(-0.5f, -0.5f, -0.75f);
                GLRenderViewport.Entities.Add(Plane);
            }
        }
        private String m_materialPath;

        public MaterialPreviewer(Window window) : base(window)
        {

        }

    }
}
