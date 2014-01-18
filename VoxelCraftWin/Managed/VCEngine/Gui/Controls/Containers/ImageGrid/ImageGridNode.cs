using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ImageGridNode : Control
    {

        public Label Label;
        public ImageView Image;

        public ImageGridNode(String label)
        {
            Image = new ImageView();
            AddControl(Image);

            // Label rendered second
            Label = new Label(label);
            Label.TextAlignment = VCEngine.Label.TextAlignments.LowerCenter;
            //Label.FontColor = Color.White;
            AddControl(Label);

            Resize += (s, a) =>
                {
                    Label.Frame = new Rectangle(5, 5, Width - 10, Height - 5);
                    Image.Frame = new Rectangle(5, 22, Width - 10, Height - 27);
                };
        }

        protected override void Draw()
        {
            //Gui.DrawButton(ScreenFrame);
            Gui.Draw9SliceImage(@"Icons\Button.DDS", ScreenFrame);
            Gui.DrawRectangle(new Rectangle(ScreenFrame.X + 5, ScreenFrame.Y + 20, Width - 10, 1), Color.Black);
        }
    }
}
