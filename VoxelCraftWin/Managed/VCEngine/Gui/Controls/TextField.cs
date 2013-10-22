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

        public event EventHandler<CharEventArgs> TextEntry = delegate { };

        private float m_nextSwapTime;
        private bool m_isCursurVisible;

        public TextField()
        {
            CharPress += OnCharPress;
            KeyPress += OnKeyPress;
            BackgroundColor = Color.White;
            BorderWidth = 1;
            CanFocus = true;
            Frame = new Rectangle(0, 0, 200, 25);
        }

        void OnKeyPress(object sender, KeyEventArgs e)
        {
            if (e.State.Key == Input.Keys.Backspace && e.State.Action != TriState.Up)
            {
                if (CursorOffset == 0)
                    return;

                if (Text.Length == CursorOffset)
                    Text = Text.Substring(0, CursorOffset - 1);

                else
                    Text = Text.Remove(CursorOffset - 1, 1);

                CursorOffset--;
                TextEntry(this, new CharEventArgs { CharCode = e.State.Key });
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
            if (Text.Length == CursorOffset)
                Text = Text + char.ConvertFromUtf32(e.CharCode);

            else
                Text = Text.Insert(CursorOffset, char.ConvertFromUtf32(e.CharCode));

            CursorOffset++;
            TextEntry(this, e);
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
