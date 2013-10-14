using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TextField : Control
    {

        public string Text;
        public Color FontColor = Color.Black;
        public TextMetrics Metrics;

        public TextField(string text)
        {
            Text = text;
            Metrics = Gui.GetMetrics(text, Font);
            Frame = new Rectangle(0, 0, Metrics.TotalWidth, Metrics.TotalHeight);
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            Gui.DrawString(Text, new Point(sf.X, sf.Y), FontColor, Font);
        }

    }
}
