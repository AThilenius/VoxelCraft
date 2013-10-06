using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MenuBar : Control
    {
        private const int c_buttonHeight = 25;
        private const int c_buttonWidth = 50;

        private Dictionary<Button, Menu> m_menues = new Dictionary<Button, Menu>();

        public MenuBar()
        {
            ScreenFrame = new Rectangle(0, Window.Size.Y - c_buttonHeight, Window.Size.X, c_buttonHeight);
            HighlightBackgroundColor = BackgroundColor;
            HightlightBorderColor = Color.Trasparent;
        }

        public void AddMenu(string title, Menu menu)
        {
            AddControl(menu);

            Button nButton = new Button(title);
            AddControl(nButton);
            nButton.Frame = new Rectangle(m_menues.Count * c_buttonWidth, 0, c_buttonWidth - 1, c_buttonHeight);
            nButton.MouseEnter += (s, a) => menu.Visible = true;
            nButton.MouseExit += (s, a) => menu.Visible = false;

            menu.Frame = new Rectangle(m_menues.Count * c_buttonWidth, -menu.Frame.Height, menu.Frame.Width, menu.Frame.Height);
            menu.Visible = false;

            m_menues.Add(nButton, menu);
        }


    }
}
