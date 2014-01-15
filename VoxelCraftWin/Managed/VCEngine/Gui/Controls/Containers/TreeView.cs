using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// Hosts a cumulative background and container for the head TreeNode
    /// </summary>
    public class TreeView : Control
    {
        
        // Dummy TreeNode
        public class Dummy : TreeNode
        {
            public override bool IsExpanded { get { return true; } }
            public override bool IsLeaf { get { return false; } }
        }

        public TreeNode Head { get { return m_head; } }

        private TreeNode m_head;
        private TreeNode m_lastClicked;

        public TreeView()
        {
            Resize += (s, a) =>
                {
                    SetHeadLocation();
                    Head.ReBuildHead();
                };
            CanFocus = true;

            // Create a dummy head
            m_head = new Dummy();
            m_head.ClientHeight = 0;
            AddControl(m_head);
            m_head.OnHeadRebuild += (s, a) => SetHeadLocation();
            m_head.OnItemClicked += (s, a) =>
            {
                if (m_lastClicked != null)
                    m_lastClicked.FocusLevel = NodeFocusLevel.None;

                m_lastClicked = (TreeNode)s;
            };
            SetHeadLocation();

        }

        private void SetHeadLocation()
        {
            m_head.Frame = new Rectangle(0, Height - m_head.Height, Width, m_head.Height);
        }

        protected override void Draw()
        {
            Gui.DrawBackgroundEmpty(ScreenFrame);
            Gui.DrawBackground(m_head.ScreenFrame);

            if (m_lastClicked != null)
            {
                if (IsFocused)
                    m_lastClicked.FocusLevel = NodeFocusLevel.ActiveClicked;

                else
                    m_lastClicked.FocusLevel = NodeFocusLevel.InActiveClicked;
            }


        }
    }
}
