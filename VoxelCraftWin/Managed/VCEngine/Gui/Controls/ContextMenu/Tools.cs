using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Tools : ToolContextComponent
    {
        private ToggleButton m_cubeButton;
        private ToggleButton m_sphereButton;
        private ToggleButton m_eyeDropButton;

        public Tools(Window window, GameWindow gameWindow) : base(window, "Tools:")
        {
            m_cubeButton = new ToggleButton(ParentWindow, "Cube Tool");
            m_cubeButton.Style = ToggleButton.ToggleStyle.TriLeft;
            m_cubeButton.OnDepressed += (sender, args) => EditorWorld.MasterGameWindow.ActiveTool = new BlockClickDragTool(ParentWindow, gameWindow);
            AddControl(m_cubeButton);

            m_sphereButton = new ToggleButton(ParentWindow, "Sphere Tool");
            m_sphereButton.Style = ToggleButton.ToggleStyle.TriCenter;
            m_sphereButton.OnDepressed += (s, a) => EditorWorld.MasterGameWindow.ActiveTool = new CircleTool(ParentWindow, gameWindow);
            AddControl(m_sphereButton);

            m_eyeDropButton = new ToggleButton(ParentWindow, "Eye Dropper");
            m_eyeDropButton.Style = ToggleButton.ToggleStyle.TriRight;
            m_eyeDropButton.OnDepressed += (sender, args) =>
                {
                    EyeDropperTool edt = new EyeDropperTool(ParentWindow, gameWindow);
                    edt.OnPicked += (s, a) => (ParentWindow as EditorWindow).VoxelEditor.ColorPicker.ColorRGB = edt.ColorRGB;
                    EditorWorld.MasterGameWindow.ActiveTool = edt;
                };
            AddControl(m_eyeDropButton);

            ToggleButton.CreateGroup(m_cubeButton, m_sphereButton, m_eyeDropButton);
            m_cubeButton.IsDepressed = true;

            Height = m_cubeButton.Height + 4;
        }

        protected override void Draw()
        {
            Gui.DrawBackground(ScreenFrame);

            int width = MathHelper.RoundedDevision(Frame.Width, 3);

            m_cubeButton.Frame = new Rectangle(width * 0, 2, width + 1, m_cubeButton.Height);
            m_sphereButton.Frame = new Rectangle(width * 1, 2, width, m_cubeButton.Height);
            m_eyeDropButton.Frame = new Rectangle(width * 2, 2, width + 1, m_cubeButton.Height);
        }

    }
}
