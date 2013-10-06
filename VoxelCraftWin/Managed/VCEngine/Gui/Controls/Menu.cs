using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Menu : Control
    {
        private const int c_buttonHeight = 25;
        private const int c_buttonWidth = 100;

        private List<Button> m_buttons = new List<Button>();

        public Menu()
        {

        }

        public Button AddItemReverse (String title)
        {
            // ReSize this
            Frame = new Rectangle(Frame.X, Frame.Y, c_buttonWidth, m_buttons.Count * c_buttonHeight + c_buttonHeight);

            Button nButton = new Button(title);
            AddControl(nButton);
            nButton.Frame = new Rectangle(0, Frame.Height - c_buttonHeight, c_buttonWidth, c_buttonHeight - 1);
            m_buttons.Add(nButton);

            return nButton;
        }

    }
}
