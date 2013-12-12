using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Header : Control
    {
        private Point m_delta = new Point(-1, -1);

        public Header()
        {
            Margin = new MarginSize();
            DragBegin += (s, a) => m_delta = GlfwInputState.InvertedMouseLocation;
            Draging += Header_Draging;
            //DoubleClick += (s, a) =>
            //    {
            //        Window.Size = Window.MonitorSize;
            //        Window.Position = new Point();
            //    };
        }

        void Header_Draging(object sender, MouseEventArgs e)
        {
            Window.Position = Window.Position + (GlfwInputState.InvertedMouseLocation - m_delta);
            GlfwInputState.InvertedMouseLocation = m_delta;
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            Gui.DrawButton(sf);
        }

    }
}