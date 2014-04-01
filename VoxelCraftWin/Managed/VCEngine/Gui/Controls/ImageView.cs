using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ImageView : Control
    {
        public Texture Image = Texture.GetInResources(@"Images\Icons\ErrorImage.DDS");

        public ImageView(Window window) : base(window)
        {
            IsEventPassthrough = true;
        }

        protected override void Draw()
        {
            Gui.DrawImage(Image, ScreenFrame);
        }

    }
}
