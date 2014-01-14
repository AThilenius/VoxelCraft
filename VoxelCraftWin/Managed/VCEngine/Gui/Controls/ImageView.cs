using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ImageView : Control
    {

        public String ImagePath = "";

        protected override void Draw()
        {
            if (ImagePath != "")
                Gui.DrawImage(ImagePath, ScreenFrame);
        }

    }
}
