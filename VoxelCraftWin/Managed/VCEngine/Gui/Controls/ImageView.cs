using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ImageView : Control
    {
        public String ImagePath = @"Icons\ErrorImage.DDS";

        public ImageView(Window window) : base(window)
        {

        }

        protected override void Draw()
        {
            if (ImagePath != "")
                GuiDrawer.DrawImage(ImagePath, ScreenFrame);
        }

    }
}
