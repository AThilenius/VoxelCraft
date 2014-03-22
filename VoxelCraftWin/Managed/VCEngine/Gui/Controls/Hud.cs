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
        private TimeSpan m_cpuTimeTotal;
        private float m_lastDeltaTime;

        private Font m_fontConsolas;
        private Texture m_hudTexture = Texture.Get(@"Icons\Hud.DDS");

        public Hud(Window window) : base(window)
        {
            HudLabel = new Label(ParentWindow, "VoxelCraft Beta 0.0.1 Thilenius");
            AddControl(HudLabel);
            HudLabel.Font = VCEngine.Font.GetFont(HudLabel.Font.Name, 16, true);

            m_fontConsolas = Font.GetFont("Consolas", 12);
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;

            GuiDrawer.Draw9SliceImage(m_hudTexture, sf, 10, 0.17f);

            HudLabel.Frame = new Rectangle(0, Height - 20, Width, HudLabel.Height);

            m_lastDeltaTime = 0.95f * m_lastDeltaTime + 0.05f * (float)Time.DeltaTime;
            m_yOffset = 35;
            m_cpuTimeTotal += Editor.LastCPUTime;

            DrawText("             CPU Time: [ " + m_cpuTimeTotal.Minutes + ":" + m_cpuTimeTotal.Seconds.ToString("00") + (m_cpuTimeTotal.TotalSeconds - (float)(int)(m_cpuTimeTotal.TotalSeconds)).ToString(".0000000") + " ]", sf);
            DrawText("   Drawn Frames Count: [ " + m_frameCount++ + " ]", sf);
            DrawText("                  FPS: [ " + (int)(1.0f / m_lastDeltaTime) + " ]", sf);

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
