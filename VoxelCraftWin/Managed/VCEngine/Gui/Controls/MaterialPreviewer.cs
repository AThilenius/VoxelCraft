using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialPreviewer : RenderWindow
    {

        public Material Material
        {
            get { return m_material; }
            set
            {
                m_material = value;
                GLRenderViewport.Entities.Clear();

                FilterRenderer.GLRenderViewport.Entities.Clear();
                RenderedEntity Plane = new RenderedEntity(@"Models\Plane.obj", @"Materials\Filters\" + ((FileInfo)node.UserData).Name);
                Plane.Transform.Position = new Vector3(-0.5f, -0.5f, -0.75f);
                FilterRenderer.GLRenderViewport.Entities.Add(Plane);
            }
        }
        private Material m_material;

        public MaterialPreviewer(Window window) : base(window)
        {

        }

    }
}
