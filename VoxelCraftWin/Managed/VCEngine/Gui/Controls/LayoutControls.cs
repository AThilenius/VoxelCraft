using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class LayoutControls : Control
    {
        public Button m_leftSlideButton;

        private Control m_containerControl;

        public LayoutControls()
        {
            Frame = new Rectangle(0, 0, 300, 0);

            m_containerControl = new Control();
            AddControl(m_containerControl);

            Resize += (s, a) => m_containerControl.Frame = new Rectangle(0, (int)Math.Round(Frame.Height / 2.0f) - 10, Frame.Width, 20);

            m_leftSlideButton = new Button("Left");
            m_containerControl.AddControl(m_leftSlideButton);
            m_leftSlideButton.Dock = Dockings.Left;
        }

        protected override void Draw()
        {
            Gui.DrawBorderedRect(ScreenFrame, Color.ControlRed, Color.ControlRed, 1);
        }

    }
}
