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
        }

        protected override void Draw()
        {
            base.Draw();

            Gui.DrawString(Title, new Point(ScreenFrame.X + 10, ScreenFrame.Y + 6), Color.Black);
        }

    }
}
