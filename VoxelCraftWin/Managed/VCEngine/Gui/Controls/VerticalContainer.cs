using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class VerticalContainer : Control
    {
        public int VerticalPadding = 5;
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

        public VerticalContainer()
        {
            Resize += VerticalContainer_Resize;
        }

        public override void AddControl(Control control)
        {
            base.AddControl(control);
            control.DockOrder = m_yOffset++;
            control.Dock = (m_order == StackingOrder.Up) ? Dockings.Bottom : Dockings.Top;
            Frame = Frame;
        }

        void VerticalContainer_Resize(object sender, ResizeEventArgs e)
        {
            //Resize container to content's summation
            
        }

        public void AddPadding(int size = 10)
        {
            //m_yOffset += size;
        }

    }
}
