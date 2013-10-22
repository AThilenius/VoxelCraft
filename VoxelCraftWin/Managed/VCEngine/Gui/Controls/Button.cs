using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Button : Control
    {

        public String Text;
        
        public Button(String title)
        {
            Text = title;
            Frame = new Rectangle(0, 0, Gui.GetMetrics(title, Font).TotalWidth, 25);
            DrawHover = true;
            BorderWidth = 1;
        }

        protected override void Draw()
        {
            base.Draw();

            if ( Enabled )
                Gui.DrawString(Text, new Point(ScreenFrame.X + 10, ScreenFrame.Y + 3 ), Color.Black, Font);

            else
                Gui.DrawString(Text, new Point(ScreenFrame.X + 10, ScreenFrame.Y + 3), Color.ControlDisabledText, Font);
        }

    }
}
