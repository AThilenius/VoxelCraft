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

        private int m_yOffset = 0;

        public override void AddControl(Control control)
        {
            base.AddControl(control);

            switch (Order)
            {
                case StackingOrder.Down:
                    m_yOffset += control.Frame.Height;
                    control.Frame = new Rectangle(0, Frame.Height - m_yOffset, Frame.Width, control.Frame.Height);
                    break;

                case StackingOrder.Up:
                    m_yOffset += control.Frame.Height;
                    control.Frame = new Rectangle(0, m_yOffset, Frame.Width, control.Frame.Height);
                    break;
            }

        }

        public override void RemoveControl(Control control)
        {
            throw new NotImplementedException();
        }

    }
}
