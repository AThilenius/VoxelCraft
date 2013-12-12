using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Label : Control
    {
        [Flags]
        public enum TextAlignments
        {
            UpperLeft,
            CenterLeft,
            LowerLeft,
            UpperCenter,
            Center,
            LowerCenter,
            UpperRight,
            CenterRight,
            LowerRight
        }

        public string Text
        {
            get { return m_text; }
            set
            {
                m_text = value;
                Metrics = Gui.GetMetrics(m_text, Font);
            }
        }
        public TextAlignments TextAlignment = TextAlignments.Center;
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
            Point ll = new Point(sf.X, sf.Y);
            
            //=====   Vertical   =======================================================
            if(TextAlignment == TextAlignments.UpperLeft || TextAlignment == TextAlignments.UpperCenter || TextAlignment == TextAlignments.UpperRight)
                ll.Y = sf.Y + sf.Height - Metrics.TotalHeight;
            
            if(TextAlignment == TextAlignments.CenterLeft || TextAlignment == TextAlignments.Center || TextAlignment == TextAlignments.CenterRight)
                ll.Y = sf.Y + MathHelper.RoundedDevision(sf.Height, 2) - MathHelper.RoundedDevision(Metrics.TotalHeight, 2);

            //=====   Horizontal   =======================================================
            if (TextAlignment == TextAlignments.LowerCenter || TextAlignment == TextAlignments.Center || TextAlignment == TextAlignments.UpperCenter)
                ll.X = sf.X + MathHelper.RoundedDevision(sf.Width, 2) - MathHelper.RoundedDevision(Metrics.TotalWidth, 2);

            if (TextAlignment == TextAlignments.LowerRight || TextAlignment == TextAlignments.CenterRight || TextAlignment == TextAlignments.UpperRight)
                ll.X = sf.X + sf.Width - Metrics.TotalHeight;

            Gui.DrawString(Text, ll, FontColor, Font);
        }

    }
}
