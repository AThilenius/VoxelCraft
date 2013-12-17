using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class VerticalContainer : Control
    {
        public enum StackingOrder
        {
            Up,
            Down
        }

        private StackingOrder m_order = StackingOrder.Down;
        public StackingOrder Order
        {
            get { return m_order; }
            set
            {
                m_order = value;
            }
        }

        private List<Control> m_orderedChildren = new List<Control>();

        public override void AddControl(Control control)
        {
            base.AddControl(control);
            m_orderedChildren.Add(control);
            Rebuild();
        }

        public void AddControlAtIndex(int index, Control control)
        {
            base.AddControl(control);
            m_orderedChildren.Insert(index, control);
            Rebuild();
        }

        public void Rebuild()
        {
            int yOffset = 0;

            for (int i = 0; i < m_orderedChildren.Count; i++)
            {
                Control ctrl = m_orderedChildren[i];

                if (!ctrl.Visible)
                    continue;

                if (m_order == StackingOrder.Down)
                    ctrl.Frame = new Rectangle(0, Frame.Height - yOffset - ctrl.Height, Width, ctrl.Height);

                else
                    ctrl.Frame = new Rectangle(0, yOffset, Width, ctrl.Height);

                yOffset += ctrl.Height;
            }
        }

        protected override void Draw()
        {
            Gui.DrawRectangle(ScreenFrame, Color.ControlRed);
        }

    }
}
