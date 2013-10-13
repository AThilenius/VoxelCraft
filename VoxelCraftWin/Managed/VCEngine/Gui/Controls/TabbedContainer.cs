using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TabbedContainer : Control
    {
        private const int c_buttonHeight = 20;
        private const int c_buttonWidth = 50;

        private Button m_activeButton;
        private Control m_activeControl;
        private int m_xOffset;

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

            Button nb = new Button(name);
            AddControl(nb);
            AddControl(control);

            nb.Frame = new Rectangle(m_xOffset, 0, c_buttonWidth, c_buttonHeight);
            control.Frame = new Rectangle(0, c_buttonHeight, sc.Width, sc.Height - c_buttonHeight);

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

            m_xOffset += c_buttonWidth;
        }

    }
}
