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
                UpdateString();
            }
        }
        public TextAlignments TextAlignment = TextAlignments.Center;
        public Color FontColor = Color.Black;
        public TextMetrics Metrics;
        public Boolean TruncateLength = true;

        private string m_text;
        private string m_renderedString;
        private TextMetrics m_subMetric;

        private ValueAnimator<Color> m_fontAnimator;

        public Label(Window window, string text) : base(window)
        {
            Text = text;
            Frame = new Rectangle(0, 0, Metrics.TotalWidth, Metrics.TotalHeight);
            Resize += (s, a) => UpdateString();
            IsEventPassthrough = true;
        }

        public void AnimateFontColor(Color to, Action onCompleation = null, float animationTime = 0.25f)
        {
            m_fontAnimator = new ValueAnimator<Color>(FontColor, to, animationTime);
            ParentWindow.ShouldRedraw(animationTime + 0.1f);

            if (onCompleation != null)
                m_fontAnimator.OnCompleation += (s, a) => onCompleation();
        }

        protected override void Draw()
        {
            base.Draw();

            // Update animations (If animating)
            if (m_fontAnimator != null)
            {
                if (m_fontAnimator.IsDoneAnimating)
                {
                    m_fontAnimator = null;
                    return;
                }

                FontColor = m_fontAnimator.GetValue();
            }

            Rectangle sf = ScreenFrame;
            Point ll = new Point(sf.X, sf.Y);
            
            //=====   Vertical   =======================================================
            if(TextAlignment == TextAlignments.UpperLeft || TextAlignment == TextAlignments.UpperCenter || TextAlignment == TextAlignments.UpperRight)
                ll.Y = sf.Y + sf.Height - m_subMetric.TotalHeight;
            
            if(TextAlignment == TextAlignments.CenterLeft || TextAlignment == TextAlignments.Center || TextAlignment == TextAlignments.CenterRight)
                ll.Y = sf.Y + MathHelper.RoundedDevision(sf.Height, 2) - MathHelper.RoundedDevision(m_subMetric.TotalHeight, 2);

            //=====   Horizontal   =======================================================
            if (TextAlignment == TextAlignments.LowerCenter || TextAlignment == TextAlignments.Center || TextAlignment == TextAlignments.UpperCenter)
                ll.X = sf.X + MathHelper.RoundedDevision(sf.Width, 2) - MathHelper.RoundedDevision(m_subMetric.TotalWidth, 2);

            if (TextAlignment == TextAlignments.LowerRight || TextAlignment == TextAlignments.CenterRight || TextAlignment == TextAlignments.UpperRight)
                ll.X = sf.X + sf.Width - m_subMetric.TotalHeight;

            Font.DrawStringBeveled(m_renderedString, ll, FontColor);
        }

        private void UpdateString()
        {
            Metrics = Font.GetMetrics(m_text);
            m_subMetric = Metrics;
            m_renderedString = m_text;

            if (!TruncateLength || Metrics.TotalWidth <= Width)
                return;

            // Truncate Length
            string subStrWithoutEllpises = m_text;
            while (m_subMetric.TotalWidth > Width && subStrWithoutEllpises.Length > 0)
            {
                subStrWithoutEllpises = subStrWithoutEllpises.Substring(0, subStrWithoutEllpises.Length - 1);
                m_subMetric = Font.GetMetrics(subStrWithoutEllpises + "...");
            }

            m_renderedString = subStrWithoutEllpises + "...";
        }

    }
}
