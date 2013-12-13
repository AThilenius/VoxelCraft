﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Header : Control
    {
        public LayoutControls LayoutControls;

        private Point m_delta = new Point(-1, -1);

        public Header()
        {
            Margin = new MarginSize();
            DragBegin += (s, a) => m_delta = GlfwInputState.InvertedMouseLocation;
            Draging += Header_Draging;
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
            Gui.DrawImage(@"Icons\PlayButton.DDS", new Rectangle(sf.X + 30, sf.Y + 15, 45, 45));
        }

    }
}