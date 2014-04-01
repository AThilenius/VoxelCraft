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

        private RenderedEntity m_currentEntity = null;
        private Quaternion m_rotationQuat = Quaternion.Identity;

        public MaterialPreviewer(Window window) : base(window)
        {
            MouseSliding += (s, a) => m_rotationQuat *= Quaternion.FromEuler(ParentWindow.GlfwInputState.DeltaMouseLocation.X * 0.05f, ParentWindow.GlfwInputState.DeltaMouseLocation.Y * 0.05f, 0.0f);
        }

        public void OpenMaterialPath(String fullPath)
        {
            GLRenderViewport.Entities.Clear();

            m_currentEntity = new RenderedEntity(Path.Combine(PathUtilities.AssetsPath, @"Models\Cube.obj"), fullPath);
            m_currentEntity.Transform.Position = new Vector3(-0.5f, -0.5f, -2.75f);
            GLRenderViewport.Entities.Add(m_currentEntity);
        }

        protected override void Draw()
        {
            base.Draw();
            
            m_rotationQuat *= Quaternion.FromAxisAngle(Vector3.One, 100.0f * Time.DeltaTime);

            if (m_currentEntity != null)
                m_currentEntity.Transform.Rotation = m_rotationQuat;
        }

    }
}
