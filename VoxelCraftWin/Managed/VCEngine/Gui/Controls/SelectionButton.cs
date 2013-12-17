using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class SelectionButton : Button
    {
        public event EventHandler OnSelection = delegate { };
        public event EventHandler OnDeSelection = delegate { };

        private List<SelectionButton> m_group;
        private bool m_isActive = false;

        public SelectionButton(String title) : base (title)
        {
            Frame = new Rectangle(0, 0, Font.GetMetrics(title).TotalWidth, 25);
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

                    button.GuiStyle = Style.PushButton;

                    if (button.m_isActive && invokeCallback)
                        button.OnDeSelection(this, EventArgs.Empty);

                    button.m_isActive = false;
                }
            }

            GuiStyle = Style.HighlightedButton;
            
            if (!m_isActive && invokeCallback)
                OnSelection(this, EventArgs.Empty);

            m_isActive = true;
        }

        void SelectionButton_Click(object sender, MouseEventArgs e)
        {
            Activate(true);
        }

        public static void CreateGroup (params SelectionButton[] buttons)
        {
            List<SelectionButton> group = new List<SelectionButton>(buttons);

            foreach (SelectionButton button in buttons)
                button.m_group = group;
        }

    }
}
