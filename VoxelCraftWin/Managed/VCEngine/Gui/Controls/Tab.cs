using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Tab : Control
    {
        public TabbedContainer ParentContainer;
        public Button TabHeaderButton;
        public Control Content;
        public int HeaderSize = 20;
        public int HorizontalPadding = 10;

        internal Tab(TabbedContainer container, string name)
        {
            Name = name;
            ParentContainer = container;
            CanFocus = true;

            Resize += (s, a) =>
            {
                if (Content != null)
                    if (ParentContainer.AlignTop)
                        Content.Frame = new Rectangle(HorizontalPadding, 0, Frame.Width - 2 * HorizontalPadding, Frame.Height - 10);

                    else
                        Content.Frame = new Rectangle(HorizontalPadding, 0, Frame.Width - 2 * HorizontalPadding, Frame.Height - HeaderSize - 10);
            };
        }

        internal void SetContent(Control content)
        {
            Content = content;
            AddControl(content);

            if (ParentContainer.AlignTop)
                Content.Frame = new Rectangle(HorizontalPadding, 0, Frame.Width - 2 * HorizontalPadding, Frame.Height - 10);

            else
                Content.Frame = new Rectangle(HorizontalPadding, 0, Frame.Width - 2 * HorizontalPadding, Frame.Height - HeaderSize - 10);

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

            if (!ParentContainer.AlignTop)
            {
                // Lower Aligned
                Rectangle sf = ScreenFrame;
                Rectangle headerBounds = new Rectangle(sf.X + HorizontalPadding, sf.Y + sf.Height - HeaderSize, sf.Width - 2 * HorizontalPadding, HeaderSize);

                if (ParentContainer.IsFocused)
                {
                    Gui.DrawRectangle(headerBounds, Color.ControlBlue);
                    Font.DrawString(Name, new Point(headerBounds.X + 5, headerBounds.Y + 2), Color.White);
                }

                else
                {
                    Gui.DrawBorderedRect(headerBounds, Color.ControlDisabled, Color.ControlVeryDark, 1);
                    Font.DrawString(Name, new Point(headerBounds.X + 5, headerBounds.Y + 2), Color.Black);
                }
            }
        }


    }
}
