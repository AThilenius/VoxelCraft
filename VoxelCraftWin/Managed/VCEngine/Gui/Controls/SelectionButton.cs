using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class SelectionButton : Control
    {
        public String Text;
        public event EventHandler OnSelection = delegate { };
        public event EventHandler OnDeSelection = delegate { };

        private List<SelectionButton> m_group;
        private bool m_isActive = false;
        private Color m_originalBackground;
        private Color m_originalBorder;

        public SelectionButton(String title)
        {
            Text = title;
            Frame = new Rectangle(0, 0, Gui.GetMetrics(title, Font).TotalWidth, 25);
            DrawHover = true;
            BorderWidth = 1;
            m_originalBackground = BackgroundColor;
            m_originalBorder = BorderColor;
            Click += SelectionButton_Click;
        }

        public void Activate(bool invokeCallback = false)
        {
            if (m_group != null)
            {
                foreach (SelectionButton button in m_group)
                {
                    if (button == this)
                        continue;

                    button.BackgroundColor = m_originalBackground;
                    button.BorderColor = m_originalBorder;

                    if (button.m_isActive && invokeCallback)
                        button.OnDeSelection(this, EventArgs.Empty);

                    button.m_isActive = false;
                }
            }

            m_originalBackground = BackgroundColor;
            m_originalBorder = BorderColor;

            BackgroundColor = HoverBackgroundColor;
            BorderColor = Color.ControlBlue;

            if (!m_isActive && invokeCallback)
                OnSelection(this, EventArgs.Empty);

            m_isActive = true;
        }

        void SelectionButton_Click(object sender, MouseEventArgs e)
        {
            Activate(true);
        }

        protected override void Draw()
        {
            base.Draw();

            if (Enabled)
                Gui.DrawString(Text, new Point(ScreenFrame.X + 10, ScreenFrame.Y + 3), Color.Black, Font);

            else
                Gui.DrawString(Text, new Point(ScreenFrame.X + 10, ScreenFrame.Y + 3), Color.ControlDisabledText, Font);
        }

        public static void CreateGroup (params SelectionButton[] buttons)
        {
            List<SelectionButton> group = new List<SelectionButton>(buttons);

            foreach (SelectionButton button in buttons)
                button.m_group = group;
        }

    }
}
