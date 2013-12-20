using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class PanelsControler : Control
    {
        private ToggleButton m_left;
        private ToggleButton m_right;

        private ValueAnimator<Point> m_leftAnimator;
        private ValueAnimator<Point> m_rightAnimator;

        public PanelsControler()
        {
            m_leftAnimator = new ValueAnimator<Point>(new Point(0, 0));
            m_rightAnimator = new ValueAnimator<Point>(new Point(Window.ScaledSize.X - 250, 0));

            m_left = new ToggleButton(" ");
            m_left.ImagePath = @"Icons\LeftPane.DDS";
            m_left.Width = 30;
            m_left.Style = ToggleButton.ToggleStyle.TriLeft;
            m_left.IsDepressed = true;
            m_left.OnRelease += (s, a) => m_leftAnimator = new ValueAnimator<Point>(new Point(0, 0), new Point(-250, 0), 0.25f);
            m_left.OnDepressed += (s, a) => m_leftAnimator = new ValueAnimator<Point>(new Point(-250, 0), new Point(0, 0), 0.25f);
            AddControl(m_left);

            m_right = new ToggleButton(" ");
            m_right.Width = 30;
            m_right.ImagePath = @"Icons\RightPane.DDS";
            m_right.Style = ToggleButton.ToggleStyle.TriRight;
            m_right.IsDepressed = true;
            m_right.OnRelease += (s, a) => m_rightAnimator = new ValueAnimator<Point>(new Point(Window.ScaledSize.X - 250, 0), new Point(Window.ScaledSize.X, 0), 0.25f);
            m_right.OnDepressed += (s, a) => m_rightAnimator = new ValueAnimator<Point>(new Point(Window.ScaledSize.X, 0), new Point(Window.ScaledSize.X - 250, 0), 0.25f);
            AddControl(m_right);

            // Manual Resize Handlers
            Window.Resize += (s, a) =>
                {
                    EditorGui.SolutionEx.Frame = new Rectangle(0, 0, 250, Window.ScaledSize.Y - 75);
                    EditorGui.RightContextMenu.Frame = new Rectangle(Window.ScaledSize.X - 250, 0, 250, Window.ScaledSize.Y - 75);

                    if (m_left.IsDepressed)
                        m_leftAnimator = new ValueAnimator<Point>(new Point(0, 0));

                    else
                        m_leftAnimator = new ValueAnimator<Point>(new Point(-250, 0));

                    if (m_right.IsDepressed)
                        m_rightAnimator = new ValueAnimator<Point>(new Point(Window.ScaledSize.X - 250, 0));

                    else
                        m_rightAnimator = new ValueAnimator<Point>(new Point(Window.ScaledSize.X, 0));
                };

            m_left.Width = m_right.Width;

            Height = m_left.Height;
            Width = m_left.Width + m_right.Width;
        }

        protected override void Draw()
        {
            int width = MathHelper.RoundedDevision(Frame.Width, 2);

            m_left.Frame = new Rectangle(width * 0, 0, width, m_left.Height);
            m_right.Frame = new Rectangle(width * 1 - 2, 0, width, m_right.Height);

            Point left = m_leftAnimator.GetValue();
            Point right = m_rightAnimator.GetValue();

            EditorGui.SolutionEx.Location = left;
            EditorGui.EditorWindow.Frame = new Rectangle(250 + left.X, 0, right.X - (left.X + 250), Window.ScaledSize.Y - 75);
            EditorGui.RightContextMenu.Location = right;
        }

    }
}
