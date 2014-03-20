using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Menu : Control
    {
        private int m_offset;

        public Menu(Window window) : base(window)
        {
            Visible = false;
            CanFocus = true;
            Layer = 1;
            Focused += (s, a) => Visible = a.IsFocused;
        }

        public Button AddItem (String title)
        {
            Button nButton = new Button(ParentWindow, title);
            nButton.GuiStyle = Button.Style.MenuButton;
            //nButton.Click += (s, a) => Control.MainControl.Focus();

            if (nButton.Width > Width)
                Width = nButton.Width;

            Height += nButton.Height;

            AddControl(nButton);
            nButton.DockOrder = m_offset++;
            nButton.Dock = Dockings.Top;

            return nButton;
        }

        public void Display()
        {
            Location = m_glfwInputState.MouseLocation - new Point(0, Height);
            Focus();
        }

        protected override void Draw()
        {
            GuiDrawer.DrawBackground(ScreenFrame);
        }

    }
}
