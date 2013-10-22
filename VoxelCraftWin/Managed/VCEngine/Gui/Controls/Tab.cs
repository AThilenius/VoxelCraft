using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Tab : Control
    {
        public TabbedContainer ParentContainer;
        public Control Content;
        public int HeaderSize = 20;
        public int HorizontalPadding = 10;

        internal Tab(TabbedContainer container, string name)
        {
            Name = name;
            ParentContainer = container;
            CanFocus = true;

            BackgroundColor = Color.Trasparent;
            HoverBackgroundColor = BackgroundColor;
        }

        internal void SetContent(Control content)
        {
            Content = content;
            AddControl(content);

            Content.Frame = new Rectangle(HorizontalPadding, 0, Frame.Width - 2 * HorizontalPadding, Frame.Height - HeaderSize - 10);
            Content.BackgroundColor = BackgroundColor;
            DeActivate();
        }

        internal void Activate()
        {
            Visible = true;
        }

        internal void DeActivate()
        {
            Visible = false;
        }

        protected override void Draw()
        {
            base.Draw();

            // Draw Title
            Rectangle sf = ScreenFrame;
            Rectangle headerBounds = new Rectangle(sf.X + HorizontalPadding, sf.Y + sf.Height - HeaderSize, sf.Width - 2 * HorizontalPadding, HeaderSize);

            if (ParentContainer.IsFocused)
            {
                Gui.DrawRectangle(headerBounds, Color.ControlBlue);
                Gui.DrawString(Name, new Point(headerBounds.X + 5, headerBounds.Y + 2), Color.White);
            }

            else
            {
                Gui.DrawBorderedRect(headerBounds, Color.ControlDisabled, Color.ControlVeryDark, 1);
                Gui.DrawString(Name, new Point(headerBounds.X + 5, headerBounds.Y + 2), Color.Black);
            }
        }



    }
}
