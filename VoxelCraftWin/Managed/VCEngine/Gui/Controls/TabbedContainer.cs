using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TabbedContainer : Control
    {
        public Dictionary<String, Tab> Tabs = new Dictionary<String, Tab>();
        public Boolean AlignTop;
        public Color TopHeaderColor = Color.ControlMediumBackground;
        public int ButtonHeight = 20;
        public int ButtonPadding = 5;

        private Button m_activeButton;
        private Tab m_activeTab;
        private int m_xOffset;

        public TabbedContainer()
        {
            CanFocus = true;
            Resize += TabbedContainer_Resize;
        }

        public Tab AddTab(string name, Control control)
        {
            Rectangle sc = ScreenFrame;

            int textWidth = Font.GetMetrics(name).TotalWidth;

            // Button
            Button nb = new Button(name);
            AddControl(nb);

            if (AlignTop)
                nb.Frame = new Rectangle(m_xOffset, sc.Height - ButtonHeight, textWidth + 20, ButtonHeight);

            else
                nb.Frame = new Rectangle(m_xOffset, 0, textWidth + 20, ButtonHeight);

            // Tab
            Tab tab = new Tab(this, name);
            AddControl(tab);
            Tabs.Add(name, tab);
            tab.SetContent(control);
            tab.TabHeaderButton = nb;

            if (AlignTop)
                tab.Frame = new Rectangle(0, 0, sc.Width, sc.Height - ButtonHeight - 2);

            else
                tab.Frame = new Rectangle(0, ButtonHeight, sc.Width, sc.Height - ButtonHeight);

            nb.Click += (sender, args) =>
                {
                    if (nb != m_activeButton)
                    {
                        // Deactivate other button and tab
                        m_activeTab.DeActivate();

                        // Activate new button and tab. God I love closures
                        m_activeButton = nb;
                        m_activeTab = tab;
                        m_activeTab.Activate();
                    }
                };

            if (m_activeButton == null)
            {
                m_activeButton = nb;
                m_activeTab = tab;
                m_activeTab.Activate();
            }

            m_xOffset += textWidth + 20 + ButtonPadding;
            return tab;
        }

        private void TabbedContainer_Resize(object sender, ResizeEventArgs e)
        {
            Rectangle sc = ScreenFrame;

            if (AlignTop)
            {
                foreach (Tab tab in Tabs.Values)
                {
                    tab.Frame = new Rectangle(0, 0, sc.Width, sc.Height - ButtonHeight);
                    tab.TabHeaderButton.Frame = new Rectangle(
                        tab.TabHeaderButton.Frame.X, 
                        sc.Height - ButtonHeight, 
                        tab.TabHeaderButton.Frame.Width, 
                        tab.TabHeaderButton.Frame.Height);
                }
            }

            else
            {
                foreach (Tab tab in Tabs.Values)
                    tab.Frame = new Rectangle(0, ButtonHeight, sc.Width, sc.Height - ButtonHeight);
            }
        }

        protected override void Draw()
        {
            base.Draw();

            Rectangle sf = ScreenFrame;
            
            // DeActivate all buttons first
            foreach (Tab tab in Tabs.Values)
            {
                Button button = tab.TabHeaderButton;
                button.Text.FontColor = Color.Black;
            }

            // Set active button
            if (IsFocused)
            {
                m_activeButton.Text.FontColor = Color.White;
            }

            else
            {
                m_activeButton.Text.FontColor = Color.Black;
            }

            // Top aligned specific
            if (AlignTop)
            {
                Gui.DrawRectangle(new Rectangle(sf.X, sf.Y + sf.Height - ButtonHeight, sf.Width, ButtonHeight), TopHeaderColor);

                if (IsFocused)
                {
                    Rectangle headerBounds = new Rectangle(sf.X, sf.Y + sf.Height - ButtonHeight - 2, sf.Width, 2);
                    Gui.DrawRectangle(headerBounds, Color.ControlBlue);
                }

                else
                {
                    Rectangle headerBounds = new Rectangle(sf.X, sf.Y + sf.Height - ButtonHeight - 2, sf.Width, 2);
                    Gui.DrawRectangle(headerBounds, Color.White);
                }
            }

        }

    }
}
