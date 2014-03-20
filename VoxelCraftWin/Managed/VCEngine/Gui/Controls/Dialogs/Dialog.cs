using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Dialog : Control
    {
        public float AnimationTime = 0.2f;

        private bool m_isAnimating;
        private bool m_isDownward;
        private float m_remainingAnimatioinTime;

        public Dialog(Window window) : base(window)
        {
            Visible = false;
            Layer = 1;
            Frame = new Rectangle(MathHelper.RoundedDevision(ParentWindow.ScaledSize.X, 2) - 200, ParentWindow.ScaledSize.Y - 80, 400, 300);
        }

        public virtual void Display()
        {
            m_remainingAnimatioinTime = AnimationTime;
            m_isAnimating = true;
            m_isDownward = true;
            Visible = true;
            Frame = new Rectangle(MathHelper.RoundedDevision(ParentWindow.ScaledSize.X, 2) - MathHelper.RoundedDevision(Width, 2), ParentWindow.ScaledSize.Y - 80, Width, Height);
            Editor.ShouldRedraw(AnimationTime);
        }

        public virtual void SetSize(Point size)
        {
            Frame = new Rectangle(MathHelper.RoundedDevision(ParentWindow.ScaledSize.X, 2) - MathHelper.RoundedDevision(size.X, 2), ParentWindow.ScaledSize.Y - 75, size.X, size.Y);
        }

        protected virtual void Hide()
        {
            m_isAnimating = true;
            m_isDownward = false;
            m_remainingAnimatioinTime = AnimationTime;
            Editor.ShouldRedraw(AnimationTime);
        }

        protected override void Draw()
        {
            if (m_isAnimating)
            {
                Rectangle sf = ScreenFrame;
                Point start = new Point(sf.X, ParentWindow.ScaledSize.Y - 75);
                Point to = new Point(sf.X, ParentWindow.ScaledSize.Y - (75 + Height));

                if (m_remainingAnimatioinTime <= 0.0)
                {
                    // Clamp value
                    if (m_isDownward)
                        ScreenFrame = new Rectangle(to, Width, Height);

                    else
                    {
                        ScreenFrame = new Rectangle(start, Width, Height);
                        Visible = false;
                    }

                    m_isAnimating = false;
                }
                else
                {
                    // Lerp
                    Point newLoc;

                    if (m_isDownward)
                        newLoc = Point.Lerp(start, to, m_remainingAnimatioinTime / AnimationTime);

                    else
                        newLoc = Point.Lerp(to, start, m_remainingAnimatioinTime / AnimationTime);

                    ScreenFrame = new Rectangle(newLoc, Width, Height);
                }

                m_remainingAnimatioinTime -= Time.DeltaTime;
            }

        }

    }
}
