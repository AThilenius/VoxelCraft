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
        private int m_xOffset;

        public void AddMenu(string title, Menu menu)
        {
            AddControl(menu);

            int textWidth = Gui.GetMetrics(title).TotalWidth;

            Button nButton = new Button(title);
            AddControl(nButton);
            nButton.Frame = new Rectangle(m_xOffset, 0, textWidth + 20, c_buttonHeight);

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
                        GlfwInputState.OnMouseClick += TemporaryMouseHandler;
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

            menu.Frame = new Rectangle(m_xOffset, -menu.Frame.Height, menu.Frame.Width, menu.Frame.Height);
            menu.Visible = false;

            m_xOffset += textWidth + 20 + 1;
            m_menues.Add(nButton, menu);
        }

        void TemporaryMouseHandler(object sender, MouseClickEventArgs e)
        {
            foreach (Button b in m_menues.Keys)
            {
                if (b.ScreenFrame.IsPointWithin(e.Location))
                    return;
            }

            if (m_lastActiveMenu != null && m_lastActiveMenu.ScreenFrame.IsPointWithin(e.Location))
                return;

            if (m_lastActiveMenu != null)
                m_lastActiveMenu.Visible = false;

            m_isActive = false;
            m_lastActiveMenu = null;
            GlfwInputState.OnMouseClick -= TemporaryMouseHandler;
        }


    }
}
