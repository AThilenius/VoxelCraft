using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ResizeBar : Control
    {
        public Boolean IsVertical;
        public Control ResizableControl;

        public ResizeBar(bool isVertical, Control resizable)
        {
            IsVertical = true;
            ResizableControl = resizable;
            Frame = new Rectangle(0, 0, 6, 6);
            Draging += ResizeBar_Draging;
        }

        void ResizeBar_Draging(object sender, MouseEventArgs e)
        {
            
        }

        protected override void Draw()
        {
            Gui.DrawBackgroundEmpty(ScreenFrame);
        }

    }
}
