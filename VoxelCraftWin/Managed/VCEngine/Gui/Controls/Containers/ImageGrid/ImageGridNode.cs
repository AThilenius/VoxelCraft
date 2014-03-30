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
        public Object Data;

        public ImageGridNode(Window window, String label, Object data) : base(window)
        {
            Image = new ImageView(ParentWindow);
            Data = data;
            AddControl(Image);

            // Label rendered second
            Label = new Label(ParentWindow, label);
            Label.TextAlignment = VCEngine.Label.TextAlignments.LowerCenter;
            AddControl(Label);

            Resize += (s, a) =>
                {
                    Label.Frame = new Rectangle(5, 5, Width - 10, Height - 5);
                    Image.Frame = new Rectangle(5, 22, Width - 10, Height - 27);
                };

            // Dragging
            CanBeginDrag = true;
            DragBegin += (s, a) => a.Message = data;
            DragDraw += (s, a) => ParentWindow.GuiDrawer.DrawImage((Texture)a.Message, new Rectangle(ParentWindow.GlfwInputState.MouseLocation, 50, 50));
            DragDrop += (s, a) => Image.Image = (Texture)a.Message;
        }

        protected override void Draw()
        {
            //Gui.DrawButton(ScreenFrame);
            GuiDrawer.Draw9SliceImage(Gui.StandardTextures.Button, ScreenFrame);
            GuiDrawer.DrawRectangle(new Rectangle(ScreenFrame.X + 5, ScreenFrame.Y + 20, Width - 10, 1), Color.Black);
        }
    }
}
