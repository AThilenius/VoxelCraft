using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public enum NodeFocusLevel
    {
        None,
        ActiveClicked,
        InActiveClicked
    }

    public abstract class TreeNode : Control
    {
        public abstract Boolean IsExpanded { get; }
        public abstract Boolean IsLeaf { get; }
        public NodeFocusLevel FocusLevel;
        public int ClientHeight = 18;
        public Rectangle ClientScreenFrame
        {
            get { return new Rectangle(ScreenFrame.X, ScreenFrame.Y + Height - ClientHeight, Width, ClientHeight); }
        }
        public int Depth
        {
            get { return m_depth; }
            set 
            { 
                m_depth = value;

                for (int i = 0; i < m_childrenLTI.Count; i++)
                    ((TreeNode)m_childrenLTI[i]).Depth = m_depth + 1;

                ReBuildLayout();
            }
        }

        // Only invoked on the head node
        public event EventHandler OnHeadRebuild = delegate { };
        public event EventHandler OnItemClicked = delegate { };
        public event EventHandler OnItemDoubleClicked = delegate { };
        
        public Object UserData;

        protected int m_depth;
        protected List<TreeNode> m_childrenLTI = new List<TreeNode>();

        public TreeNode()
        {
            Click += (s, a) => GetHead().OnItemClicked(this, EventArgs.Empty);
            DoubleClick += (s, a) => GetHead().OnItemDoubleClicked(this, EventArgs.Empty);
        }

        public override void AddControl(Control control)
        {
            base.AddControl(control);

            if (!(control is TreeNode))
                return;

            m_childrenLTI.Add((TreeNode)control);
            ((TreeNode)control).Depth = Depth + 1;
            control.Visible = IsExpanded;

            ReBuildHead();
        }

        public override void RemoveControl(Control control)
        {
            base.RemoveControl(control);

            if (!(control is TreeNode))
                return;

            ((TreeNode)control).Depth = 0;
            m_childrenLTI.Remove((TreeNode)control);
            control.Visible = true;
            ReBuildHead();
        }

        public void Expand()
        {
            for (int i = 0; i < m_childrenLTI.Count; i++)
                m_childrenLTI[i].Visible = true;

            ReBuildHead();
        }

        public void Collapse()
        {
            for (int i = 0; i < m_childrenLTI.Count; i++)
                m_childrenLTI[i].Visible = false;

            ReBuildHead();
        }

        public void ReBuildHead()
        {
            TreeNode head = GetHead();
            head.ReBuildLayout();
            head.OnHeadRebuild(this, EventArgs.Empty);
        }

        // Invoked from the head down, depth first
        protected virtual void ReBuildLayout()
        {
            int runningYOffset = 0;

            for (int i = m_childrenLTI.Count - 1; i >= 0; i--)
            {

                TreeNode node = m_childrenLTI[i];

                if (!node.Visible)
                    continue;

                // Depth First
                node.ReBuildLayout();
                node.m_frame = new Rectangle(0, runningYOffset, Width, node.Height);
                runningYOffset += node.Height;
            }

            runningYOffset += ClientHeight;

            // Do not invoke callback
            m_frame = new Rectangle(m_frame.X, m_frame.Y, m_frame.Width, runningYOffset);
        }

        private TreeNode GetHead()
        {
            TreeNode cursor = this;
            while (cursor.Parent != null && cursor.Parent is TreeNode)
                cursor = (TreeNode) cursor.Parent;

            return cursor;
        }

        protected override void Draw()
        {
            Gui.DrawRectangle(ClientScreenFrame, new Color(0, 255, 0, 100));
        }

    }
}
