using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TreeView : Control
    {
        public int VerticalPadding = 0;

        protected int m_yOffset = 0;
        protected List<TreeViewItem> m_childrenTVI = new List<TreeViewItem>();
        protected Boolean m_needsRebuild;

        public TreeView()
        {
            Resize += TreeView_Resize;
        }

        void TreeView_Resize(object sender, ResizeEventArgs e)
        {
            NotifyUpdate();
        }

        public void AddItem(TreeViewItem control)
        {
            AddControl(control);
            m_childrenTVI.Add(control);
        }

        public void NotifyUpdate()
        {
            m_needsRebuild = true;
        }
        
        protected override void Draw()
        {
            if (m_needsRebuild)
            {
                m_yOffset = 0;

                foreach (TreeViewItem child in m_childrenTVI)
                    Rebuild(child);

                m_needsRebuild = false;
            }

            base.Draw();
        }

        private void Rebuild(TreeViewItem item, int indentCount = 1)
        {
            item.IndentationCount = indentCount;
            item.Visible = true;
            m_yOffset += item.Frame.Height + VerticalPadding;
            item.Frame = new Rectangle(0, Frame.Height - m_yOffset, Frame.Width, item.Frame.Height);

            if (!item.IsExpanded)
                SetAllChildrenVisibuilty(item, false);

            else
            {
                indentCount++;

                foreach (TreeViewItem child in item.TreeViewChildren)
                    Rebuild(child, indentCount);
            }
        }

        private void SetAllChildrenVisibuilty(TreeViewItem item, bool visible)
        {
            foreach (TreeViewItem child in item.TreeViewChildren)
            {
                child.Visible = visible;
                SetAllChildrenVisibuilty(child, visible);
            }
        }
    }
}
