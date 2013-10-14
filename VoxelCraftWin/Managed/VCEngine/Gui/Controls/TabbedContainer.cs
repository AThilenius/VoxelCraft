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

        private Button m_activeButton;
        private Control m_activeControl;
        private int m_xOffset;

        public int Padding = 10;

        public TabbedContainer()
        {
        }

        //protected override void Draw()
        //{
        //    // Suppress background drawing
        //}

        public void AddTab(string name, Control control)
        {
            Rectangle sc = ScreenFrame;

            int textWidth = Gui.GetMetrics(name).TotalWidth;
            Button nb = new Button(name);
            AddControl(nb);
            AddControl(control);

            nb.Frame = new Rectangle(m_xOffset, 0, textWidth + 20, c_buttonHeight);
            control.Frame = new Rectangle(Padding, c_buttonHeight + Padding, sc.Width - 2 * Padding, sc.Height - c_buttonHeight - 2 * Padding);

            nb.Click += (sender, args) =>
                {
                    m_activeButton.BackgroundColor = Color.ControlLight;
                    m_activeButton.HighlightBackgroundColor = Color.White;
                    m_activeControl.Visible = false;

                    m_activeButton = nb;
                    m_activeControl = control;
                    nb.BackgroundColor = Color.ControlBlue;
                    nb.HighlightBackgroundColor = Color.ControlBlue;
                    control.Visible = true;
                };

            if (m_activeButton == null)
            {
                m_activeButton = nb;
                m_activeControl = control;
                nb.BackgroundColor = Color.ControlBlue;
                nb.HighlightBackgroundColor = Color.ControlBlue;
            }

            else
            {
                control.Visible = false;
            }

            m_xOffset += textWidth + 20 + c_buttonPadding;
        }

    }
}
