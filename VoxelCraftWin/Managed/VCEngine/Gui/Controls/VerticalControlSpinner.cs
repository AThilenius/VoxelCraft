using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class VerticalControlSpinner : Control
    {
        public float AnimatrionTime = 0.25f;

        private int m_selectedIndex;
        private Dictionary<Control, ValueAnimator<Point>> m_animators = new Dictionary<Control, ValueAnimator<Point>>();

        public VerticalControlSpinner()
        {
            Resize += (s, a) =>
                {
                    ReBuildSpinner();
                };
        }


        public override void AddControl(Control control)
        {
            base.AddControl(control);
            ReBuildSpinner();
        }

        public override void RemoveControl(Control control)
        {
            base.RemoveControl(control);
            ReBuildSpinner();
        }

        public void Select(Control ctrl)
        {
            m_selectedIndex = Children.IndexOf(ctrl);

            for (int i = 0; i < Children.Count; i++)
            {
                Control child = Children[i];
                int offsetIndex = i - m_selectedIndex;
                m_animators[child] = new ValueAnimator<Point>(child.Location, new Point(0, -(offsetIndex * Height)), AnimatrionTime);
            }
        }

        protected void ReBuildSpinner()
        {
            m_animators.Clear();

            for (int i = 0; i < Children.Count; i++)
            {
                Control ctrl = Children[i];
                int offsetIndex = i - m_selectedIndex;
                ctrl.Frame = new Rectangle(0, -(offsetIndex * Height), Size);
                m_animators.Add(ctrl, new ValueAnimator<Point>( new Point(0, -(offsetIndex * Height)) ));
            }
        }

        protected override void Draw()
        {
            foreach (var KVP in m_animators)
                KVP.Key.Location = KVP.Value.GetValue();

            Gui.DrawRectangle(ScreenFrame, new Color(255, 0, 0, 100));
        }

    }
}
