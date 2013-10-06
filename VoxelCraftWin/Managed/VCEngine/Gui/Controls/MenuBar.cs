using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MenuBar : Control
    {
        private const int c_buttonHeight = 20;
        private const int c_buttonWidth = 50;

        private Dictionary<Button, Menu> m_menues = new Dictionary<Button, Menu>();
        private bool m_isActive;
        private Menu m_lastActiveMenu;

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

            // When  clicked, activate control, register OnClick handler
            // On Mouse Enter, activate menu
            // OnClick if mouse outside all buttons && active control, deactivate, unregister handler

            nButton.Click += (s, a) =>
                {
                    if (!m_isActive)
                    {
                        m_isActive = true;
                        m_menues[nButton].Visible = true;
                        m_lastActiveMenu = m_menues[nButton];
                        Input.MouseClick += TemporaryMouseHandler;
                    }
                };

            nButton.MouseEnter += (s, a) =>
                {
                    if (m_isActive)
                    {
                        if (m_lastActiveMenu != null)
                            m_lastActiveMenu.Visible = false;

                        m_lastActiveMenu = menu;
                        menu.Visible = true;
                    }
                };

            menu.Frame = new Rectangle(m_menues.Count * c_buttonWidth, -menu.Frame.Height, menu.Frame.Width, menu.Frame.Height);
            menu.Visible = false;

            m_menues.Add(nButton, menu);
        }

        void TemporaryMouseHandler(object sender, MouseClickEventArgs e)
        {
            foreach (Button b in m_menues.Keys)
            {
                if (b.ScreenFrame.IsPointWithin(e.ScreenLocation))
                    return;
            }

            if (m_lastActiveMenu != null && m_lastActiveMenu.ScreenFrame.IsPointWithin(e.ScreenLocation))
                return;

            if (m_lastActiveMenu != null)
                m_lastActiveMenu.Visible = false;

            m_isActive = false;
            m_lastActiveMenu = null;
            Input.MouseClick -= TemporaryMouseHandler;
        }


    }
}
