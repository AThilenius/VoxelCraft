using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TextField : Control
    {
        public String Text
        {
            get { return m_text; }
            set
            {
                m_text = value;
                CursorOffset = m_text.Length;
            }
        }
        public int CursorOffset;
        public Color FontColor = Color.Black;

        public event EventHandler<CharEventArgs> TextEntry = delegate { };
        public event EventHandler EnterPressed = delegate { };

        private String m_text = "";
        private float m_nextSwapTime;
        private bool m_isCursurVisible;

        public TextField()
        {
            CharPress += OnCharPress;
            RawKeyChange += OnKeyPress;
            CanFocus = true;
            Frame = new Rectangle(0, 0, 200, Font.GetMetrics("A").TotalHeight + 5);
        }

        void OnKeyPress(object sender, KeyEventArgs e)
        {
            if (e.Key == Input.Keys.Backspace && e.State != TriState.Up)
            {
                if (CursorOffset == 0)
                    return;

                if (m_text.Length == CursorOffset)
                    m_text = m_text.Substring(0, CursorOffset - 1);

                else
                    m_text = m_text.Remove(CursorOffset - 1, 1);

                CursorOffset--;
                TextEntry(this, new CharEventArgs { Char = e.Key });
            }

            if (e.Key == Input.Keys.Left && e.State != TriState.Up)
            {
                if (CursorOffset == 0)
                    return;

                CursorOffset--;
                m_nextSwapTime = Time.TotalTime += 0.5f;
                m_isCursurVisible = true;
            }

            if (e.Key == Input.Keys.Right && e.State != TriState.Up)
            {
                if (CursorOffset < m_text.Length)
                    CursorOffset++;

                m_nextSwapTime = Time.TotalTime += 0.5f;
                m_isCursurVisible = true;
            }

            if (e.Key == Input.Keys.Enter && e.State != TriState.Up)
                EnterPressed(this, EventArgs.Empty);

        }

        void OnCharPress(object sender, CharEventArgs e)
        {
            if (m_text.Length == CursorOffset)
                m_text = m_text + char.ConvertFromUtf32(e.Char);

            else
                m_text = m_text.Insert(CursorOffset, char.ConvertFromUtf32(e.Char));

            CursorOffset++;
            TextEntry(this, e);
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;

            if (IsFocused)
                Gui.DrawBackground(ScreenFrame);
            else
                Gui.DrawBackgroundEmpty(ScreenFrame);

            // Draw Text
            Font.DrawString(m_text, new Point(sf.X + 5, sf.Y + 2), FontColor);

            // Draw Cursor
            if (Time.TotalTime > m_nextSwapTime)
            {
                m_nextSwapTime += 0.5f;
                m_isCursurVisible = !m_isCursurVisible;
            }

            if (m_isCursurVisible && IsFocused)
            {
                TextMetrics cursorMetrics = Font.GetMetrics(m_text.Substring(0, CursorOffset));
                Gui.DrawRectangle(new Rectangle(sf.X + 5 + cursorMetrics.TotalWidth, sf.Y + 5, 1, sf.Height - 10), Color.Black);
            }
        }

    }
}
