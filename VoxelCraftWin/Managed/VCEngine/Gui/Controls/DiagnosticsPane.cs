using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class DiagnosticsPane : Control
    {
        private const int c_verticalSpacing = 20;

        private float m_lastDeltaTime = 0.001f;
        private int m_yOffset = 0;

        protected override void Draw()
        {
            base.Draw();
            Rectangle sf = ScreenFrame;

            m_lastDeltaTime = 0.95f * m_lastDeltaTime + 0.05f * Time.DeltaTime;
            m_yOffset = c_verticalSpacing;

            DrawText("Frame Time: " + (int)Math.Round(m_lastDeltaTime * 1000.0f) + " ms.", sf);
            DrawText("Estimated FPS: " + (int)Math.Round(1.0f / m_lastDeltaTime), sf);
            DrawText("Main Camera: " + Camera.MainCamera.Transform.Position.ToString("n2"), sf);
            DrawText("Mouse: " + Input.MousePoistion, sf);
        }

        private void DrawText(string text, Rectangle sf)
        {
            Gui.DrawString(text, new Point(sf.X + 5, sf.Y + sf.Height - m_yOffset), Color.Black);
            m_yOffset += c_verticalSpacing;
        }

    }
}
