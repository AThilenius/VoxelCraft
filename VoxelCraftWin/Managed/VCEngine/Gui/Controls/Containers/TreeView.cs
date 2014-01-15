using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// Hosts a cumulative background and container for the head TreeNode
    /// </summary>
    public class TreeView<T> : Control where T : TreeNode
    {
        public T Head
        {
            get { return m_head; }
            set
            {
                m_head = value;
                AddControl(value);
                m_head.ReBuildHead();
                m_head.OnHeadRebuild += (s, a) => SetHeadLocation();
                m_head.OnItemClicked += (s, a) =>
                    {
                        if (m_lastClicked != null)
                            m_lastClicked.FocusLevel = NodeFocusLevel.None;

                        m_lastClicked = (TreeNode)s;
                    };
                SetHeadLocation();
            }
        }

        private T m_head;
        private TreeNode m_lastClicked;

        public TreeView()
        {
            Resize += (s, a) => SetHeadLocation();
            CanFocus = true;
        }

        private void SetHeadLocation()
        {
            if (m_head != null)
                m_head.Frame = new Rectangle(0, Height - m_head.Height, Width, m_head.Height);
        }

        protected override void Draw()
        {
            Gui.DrawBackgroundEmpty(ScreenFrame);
            Gui.DrawBackground(m_head.ScreenFrame);

            if (m_lastClicked != null)
            {
                if (IsFocused)
                {
                    Gui.DrawButtonHighlighted(m_lastClicked.ClientScreenFrame);
                    m_lastClicked.FocusLevel = NodeFocusLevel.ActiveClicked;
                }

                else
                {
                    Gui.DrawButtonAccentuated(m_lastClicked.ClientScreenFrame);
                    m_lastClicked.FocusLevel = NodeFocusLevel.InActiveClicked;
                }
            }


        }
    }
}
