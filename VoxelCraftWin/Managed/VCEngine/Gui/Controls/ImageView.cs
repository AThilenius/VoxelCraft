using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ImageView : Control
    {
        public Texture Image = Texture.Get(@"Icons\ErrorImage.DDS");

        public ImageView(Window window) : base(window)
        {

        }

        protected override void Draw()
        {
            GuiDrawer.DrawImage(Image, ScreenFrame);
        }

    }
}
