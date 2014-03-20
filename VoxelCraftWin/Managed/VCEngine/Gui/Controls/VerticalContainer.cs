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

        private int m_yOffset;

        public VerticalContainer(Window window) : base(window)
        {

        }

        public override void AddControl(Control control)
        {
            base.AddControl(control);
            control.DockOrder = m_yOffset++;
            control.Dock = Dockings.Top;
        }

    }
}
