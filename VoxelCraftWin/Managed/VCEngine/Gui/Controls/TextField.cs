using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TextField : Control
    {
        public String Text = "";
        public int CursorOffset;
        public Color FontColor = Color.Black;

        private float m_nextSwapTime;
        private bool m_isCursurVisible;

        public TextField()
        {
            CharPress += OnCharPress;
            KeyPress += OnKeyPress;
            BorderWidth = 1;
            BorderColor = Color.Trasparent;
            CanFocus = true;
        }

        void OnKeyPress(object sender, KeyEventArgs e)
        {
            if (e.State.Key == Input.Keys.Backspace && e.State.Action != TriState.Up)
            {
                if (CursorOffset == 0)
                    return;

                Text = Text.Substring(0, Text.Length - 1);
                CursorOffset--;
            }

            if (e.State.Key == Input.Keys.Left && e.State.Action != TriState.Up)
            {
                if (CursorOffset == 0)
                    return;

                CursorOffset--;
                m_nextSwapTime = Time.TotalTime += 0.5f;
                m_isCursurVisible = true;
            }

            if (e.State.Key == Input.Keys.Right && e.State.Action != TriState.Up)
            {
                if (CursorOffset < Text.Length)
                    CursorOffset++;

                m_nextSwapTime = Time.TotalTime += 0.5f;
                m_isCursurVisible = true;
            }
        }

        void OnCharPress(object sender, CharEventArgs e)
        {
            Text = Text + char.ConvertFromUtf32(e.CharCode);
            CursorOffset++;
        }

        protected override void Draw()
        {
            base.Draw();
            Rectangle sf = ScreenFrame;

            // Draw Text
            Gui.DrawString(Text, new Point(sf.X + 5, sf.Y + 2), FontColor, Font);

            // Draw Cursor
            if (Time.TotalTime > m_nextSwapTime)
            {
                m_nextSwapTime += 0.5f;
                m_isCursurVisible = !m_isCursurVisible;
            }

            if (m_isCursurVisible && IsFocused)
            {
                TextMetrics cursorMetrics = Gui.GetMetrics(Text.Substring(0, CursorOffset), Font);
                Gui.DrawRectangle(new Rectangle(sf.X + 5 + cursorMetrics.TotalWidth, sf.Y + 5, 1, sf.Height - 10), Color.Black);
            }
        }

    }
}
