using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Button : Control
    {

        public String Title;

        public Button(String title)
        {
            Title = title;
            Frame = new Rectangle(0, 0, Gui.GetMetrics(title, Font).TotalWidth, 20);
        }

        protected override void Draw()
        {
            base.Draw();
            Gui.DrawString(Title, new Point(ScreenFrame.X + 10, ScreenFrame.Y ), Color.Black, Font);
        }

    }
}
