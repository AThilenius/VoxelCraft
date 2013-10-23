using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TabbedContainer : Control
    {
        private const int c_buttonHeight = 20;
        private const int c_buttonPadding = 3;

        public Dictionary<String, Tab> Tabs = new Dictionary<String, Tab>();

        private Button m_activeButton;
        private Tab m_activeTab;
        private int m_xOffset;

        public TabbedContainer()
        {
            CanFocus = true;
            HoverBackgroundColor = BackgroundColor;
            Resize += TabbedContainer_Resize;
        }

        public void AddTab(string name, Control control)
        {
            Rectangle sc = ScreenFrame;

            int textWidth = Gui.GetMetrics(name).TotalWidth;

            // Button
            Button nb = new Button(name);
            AddControl(nb);
            nb.Frame = new Rectangle(m_xOffset, 0, textWidth + 20, c_buttonHeight);
            nb.BorderWidth = 0;

            // Tab
            Tab tab = new Tab(this, name);
            AddControl(tab);
            Tabs.Add(name, tab);
            tab.Frame = new Rectangle(0, c_buttonHeight, sc.Width, sc.Height - c_buttonHeight);
            tab.SetContent(control);

            nb.Click += (sender, args) =>
                {
                    if (nb != m_activeButton)
                    {
                        // Deactivate other button and tab
                        m_activeButton.BackgroundColor = Color.ControlMediumBackground;
                        m_activeTab.DeActivate();

                        // Activate new button and tab. God I love closures
                        m_activeButton = nb;
                        m_activeTab = tab;
                        m_activeTab.Activate();
                        nb.BackgroundColor = Color.White;
                    }
                };

            if (m_activeButton == null)
            {
                m_activeButton = nb;
                m_activeTab = tab;
                m_activeTab.Activate();

                nb.BackgroundColor = Color.White;
            }

            m_xOffset += textWidth + 20 + c_buttonPadding;
        }

        private void TabbedContainer_Resize(object sender, ResizeEventArgs e)
        {
            Rectangle sc = ScreenFrame;

            foreach ( Tab tab in Tabs.Values )
                tab.Frame = new Rectangle(0, c_buttonHeight, sc.Width, sc.Height - c_buttonHeight);
        }

        protected override void Draw()
        {
            base.Draw();
        }

    }
}
