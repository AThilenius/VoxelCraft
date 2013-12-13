using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Menu : Control
    {
        private int m_offset;

        public Menu()
        {
            Visible = false;
            Frame = new Rectangle(0, 0, 100, 200);
        }

        public Button AddItem (String title)
        {
            Button nButton = new Button(title);

            if (nButton.Frame.Width > Frame.Width)
                Frame = new Rectangle(Frame.X, Frame.Y, nButton.Frame.Width, Frame.Height);

            AddControl(nButton);
            nButton.DockOrder = m_offset++;
            nButton.Dock = Dockings.Top;

            Frame = new Rectangle(Frame.X, Frame.Y + nButton.Frame.Height, nButton.Frame.Width, Frame.Height);

            return nButton;
        }

        public void DisplayAt(Point location)
        {
            Frame = new Rectangle(location, Frame.Width, Frame.Height);
            Visible = true;
        }

        public void Hide()
        {
            Visible = false;
        }

        protected override void Draw()
        {
            Gui.DrawRectangle(ScreenFrame, Color.ControlRed);
        }

    }
}
