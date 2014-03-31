using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialPreviewer : RenderWindow
    {
        public enum MaterialDisplayMode
        {
            Cube,
            Plane
        }

        public ToggleButton PlaneButton;
        public ToggleButton CubeButton;
        public MaterialDisplayMode DisplayMode
        {
            get { return m_displayMode; }
            set
            {
                m_displayMode = value;

                if (m_materialPath != "")
                    OpenMaterialPath(m_materialPath);
            }
        }

        private RenderedEntity m_currentEntity = null;
        private Boolean m_animate = true;
        private Quaternion m_rotationQuat = Quaternion.Identity;
        private MaterialDisplayMode m_displayMode = MaterialDisplayMode.Cube;
        private String m_materialPath = "";

        public MaterialPreviewer(Window window) : base(window)
        {
            CubeButton = new ToggleButton(window, "Cube");
            AddControl(CubeButton);
            CubeButton.Style = ToggleButton.ToggleStyle.TriLeft;
            CubeButton.OnDepressed += (s, a) =>
                {
                    m_displayMode = MaterialDisplayMode.Cube;
                    if (m_materialPath != "")
                        OpenMaterialPath(m_materialPath);
                };

            PlaneButton = new ToggleButton(window, "Plane");
            AddControl(PlaneButton);
            PlaneButton.Style = ToggleButton.ToggleStyle.TriRight;
            PlaneButton.OnDepressed += (s, a) =>
                {
                    m_displayMode = MaterialDisplayMode.Plane;
                    if (m_materialPath != "")
                        OpenMaterialPath(m_materialPath);
                };

            ToggleButton.CreateGroup(CubeButton, PlaneButton);
            CubeButton.Activate();

            MouseSliding += (s, a) => m_rotationQuat *= Quaternion.FromEuler(ParentWindow.GlfwInputState.DeltaMouseLocation.X * 0.05f, ParentWindow.GlfwInputState.DeltaMouseLocation.Y * 0.05f, 0.0f);
            GLRenderViewport.MainCamera.Orthographic = true;
        }

        public void OpenMaterialPath(String fullPath)
        {
            m_materialPath = fullPath;
            PathUtilities.TestFileExistance(fullPath);

            GLRenderViewport.Entities.Clear();

            switch(m_displayMode)
            {
                case MaterialDisplayMode.Cube:
                    m_currentEntity = new RenderedEntity(Path.Combine(PathUtilities.AssetsPath, @"Models\Cube.obj"), fullPath);
                    m_currentEntity.Transform.Position = new Vector3(-0.5f, -0.5f, -2.75f);
                    GLRenderViewport.MainCamera.Orthographic = false;
                    m_animate = true;
                    break;
                case MaterialDisplayMode.Plane:
                    m_currentEntity = new RenderedEntity(Path.Combine(PathUtilities.AssetsPath, @"Models\Plane.obj"), fullPath);
                    GLRenderViewport.MainCamera.Orthographic = true;
                    GLRenderViewport.MainCamera.OrthographicWidth = GLRenderViewport.MainCamera.AspectRatio;
                    m_currentEntity.Transform.Position = new Vector3(-0.5f, -0.5f, -1.0f);
                    m_animate = false;
                    break;
            }

            GLRenderViewport.Entities.Add(m_currentEntity);
        }

        protected override void Draw()
        {
            base.Draw();

            CubeButton.Frame = new Rectangle(Width - 220, 20, 100, PlaneButton.Height);
            PlaneButton.Frame = new Rectangle(Width - 122, 20, 100, CubeButton.Height);

            if (m_animate)
                m_rotationQuat *= Quaternion.FromAxisAngle(Vector3.One, 0.25f * Time.DeltaTime);
            else
                m_rotationQuat = Quaternion.Identity;

            if (m_currentEntity != null)
                m_currentEntity.Transform.Rotation = m_rotationQuat;
        }

    }
}
