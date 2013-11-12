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
        private List<KeyState> m_activateStates = new List<KeyState>();
        private List<MouseClickEventArgs> m_mouseStates = new List<MouseClickEventArgs>();

        internal DiagnosticsPane()
        {
            //Input.KeyClicked += (s, a) =>
            //    {
            //        if (a.State.Action == TriState.Pressed)
            //            m_activateStates.Add(a.State);

            //        else if (a.State.Action == TriState.Up)
            //            m_activateStates.Remove(a.State);
            //    };

            //Input.MouseClick += (s, a) =>
            //    {
            //        if (a.Action == TriState.Pressed)
            //            m_mouseStates.Add(a);

            //        else if (a.Action == TriState.Up)
            //            m_mouseStates.Remove(a);
            //    };
        }

        protected override void Draw()
        {
            base.Draw();
            Rectangle sf = ScreenFrame;

            m_lastDeltaTime = 0.95f * m_lastDeltaTime + 0.05f * Time.DeltaTime;
            m_yOffset = c_verticalSpacing;

            DrawText("Frame Time: " + (int)Math.Round(m_lastDeltaTime * 1000.0f) + " ms.", sf);
            DrawText("Estimated FPS: " + (int)Math.Round(1.0f / m_lastDeltaTime), sf);
            DrawText("Mouse: " + Input.MousePoistion, sf);

            DrawText("", sf);
            DrawText("Mouse Inputs:", sf);

            for ( int i = 0; i < 10; i++ )
                if (Input.GetMouse(i) != TriState.None)
                    DrawText(i.ToString(), sf);
            //if (m_mouseStates.Count == 0)
            //    DrawText("Mouse Inputs: None", sf);
            //else
            //{
            //    DrawText("Mouse Inputs:", sf);

            //    foreach (MouseClickEventArgs a in m_mouseStates)
            //        DrawText("Button: " + a.Button + ". Mods: " + a.Modifiers, sf);
            //}

            //if (m_activateStates.Count == 0)
            //    DrawText("Key Inputs: None", sf);
            //else
            //{
            //    DrawText("Key Inputs:", sf);

            //    foreach (KeyState s in m_activateStates)
            //        DrawText("Key: " + s.Key + ". Mods: " + s.Modifiers, sf);
            //}

        }

        private void DrawText(string text, Rectangle sf)
        {
            Gui.DrawString(text, new Point(sf.X + 5, sf.Y + sf.Height - m_yOffset), Color.Black);
            m_yOffset += c_verticalSpacing;
        }

    }
}
