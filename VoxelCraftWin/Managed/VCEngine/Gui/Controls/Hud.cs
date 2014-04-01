using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Hud : Control
    {
        public Label HudLabel;
        private int m_yOffset;
        private int m_frameCount;
        private Double m_lastLoopTime;
        private Double m_lastDrawTime;

        private Font m_fontConsolas;
        private Texture m_hudTexture = Texture.GetInResources(@"Images\Icons\Hud.DDS");

        public Hud(Window window) : base(window)
        {
            HudLabel = new Label(ParentWindow, "VoxelCraft Beta 0.0.1 Thilenius");
            AddControl(HudLabel);
            HudLabel.Font = VCEngine.Font.GetFont(HudLabel.Font.Name, 16, ParentWindow, true);

            m_fontConsolas = Font.GetFont("Consolas", 12, ParentWindow);
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            GuiDrawer.Draw9SliceImage(m_hudTexture, sf, 10, 0.17f);
            HudLabel.Frame = new Rectangle(0, Height - 20, Width, HudLabel.Height);

            // Smooth out FPS values
            m_lastLoopTime = m_lastLoopTime * 0.99d + ParentWindow.LastLoopTime.TotalSeconds * 0.01d;
            m_lastDrawTime = m_lastDrawTime * 0.99d + ParentWindow.LastDrawTime.TotalSeconds * 0.01d;

            m_yOffset = 35;
            DrawText("        Full Loop FPS: [ " + (1.0d / m_lastLoopTime).ToString("0000") + " ]", sf);
            DrawText("           OpenGL FPS: [ " + (1.0d / m_lastDrawTime).ToString("0000") + " ]", sf);
            DrawText("   Drawn Frames Count: [ " + m_frameCount++ + " ]", sf);

            m_yOffset = 35;
            DrawText("           Resolution: " + ParentWindow.TrueSize, sf, 220);
            DrawText("Gui Scaled Resolution: " + ParentWindow.ScaledSize, sf, 220);
            DrawText("                Mouse: " + m_glfwInputState.MouseLocation, sf, 220);
        }

        private void DrawText(string text, Rectangle sf, int xOffset = 0)
        {
            m_fontConsolas.DrawStringBeveled(text, new Point(sf.X + 5 + xOffset, sf.Y + sf.Height - m_yOffset), Color.Black);
            m_yOffset += 10;
        }
    }
}
