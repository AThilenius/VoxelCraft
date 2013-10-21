using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Label : Control
    {

        public string Text
        {
            get { return m_text; }
            set
            {
                m_text = value;
                Metrics = Gui.GetMetrics(m_text, Font);
            }
        }
        public Color FontColor = Color.Black;
        public TextMetrics Metrics;

        private string m_text;

        public Label(string text)
        {
            Text = text;
            Frame = new Rectangle(0, 0, Metrics.TotalWidth, Metrics.TotalHeight);
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            Gui.DrawString(Text, new Point(sf.X, sf.Y), FontColor, Font);
        }

    }
}
