using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MainPagesPicker : Control
    {
        public int ButtonWidth = 80;

        private MainPageBase m_lastSelected;
        private List<MainPageBase> m_pages = new List<MainPageBase>();

        public MainPagesPicker(Window window) : base(window)
        {
        }

        public override void AddControl(Control control)
        {
            if (!(control is MainPageBase))
                return;

            RemoveAllControls();
            m_pages.Add(control as MainPageBase);
            List<ToggleButton> toggleButtons = new List<ToggleButton>();

            for (int i = 0; i < m_pages.Count; i++)
            {
                MainPageBase page = m_pages[i];
                ToggleButton button = new ToggleButton(ParentWindow, page.Name);
                toggleButtons.Add(button);
                base.AddControl(button);

                if ( i == 0 )
                    button.Style = ToggleButton.ToggleStyle.TriLeft;

                else if (i > 0 && i < m_pages.Count - 1)
                    button.Style = ToggleButton.ToggleStyle.TriCenter;

                else if (i == m_pages.Count - 1)
                    button.Style = ToggleButton.ToggleStyle.TriRight;

                button.OnDepressed += (s, a) =>
                {
                    (ParentWindow as EditorWindow).MainSpinner.Select(page);

                    if (m_lastSelected != null)
                        m_lastSelected.OnDeselected();

                    page.OnSelected();
                };

                button.Frame = new Rectangle(ButtonWidth * i - 2 * i, 0, ButtonWidth, button.Height);
            }

            // Create Group
            if (toggleButtons.Count > 0)
            {
                ToggleButton.CreateGroup(toggleButtons.ToArray());
                toggleButtons[0].Activate();

                Height = toggleButtons[0].Height;
                Width = m_pages.Count * ButtonWidth - 2 * m_pages.Count;
            }
        }

    }
}
