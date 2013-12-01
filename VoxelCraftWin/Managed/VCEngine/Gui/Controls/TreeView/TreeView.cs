using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TreeView : Control
    {
        public int VerticalPadding = 0;

        private int m_yOffset = 0;
        private List<TreeViewItem> m_children = new List<TreeViewItem>();
        private Boolean m_needsRebuild;

        public void AddItem(TreeViewItem control)
        {
            AddControl(control);
            m_children.Add(control);
        }

        public void NotfyUpdate()
        {
            m_needsRebuild = true;
        }
        
        protected override void Draw()
        {
            if (m_needsRebuild)
            {
                m_yOffset = 0;

                foreach (TreeViewItem child in m_children)
                    Rebuild(child);

                m_needsRebuild = false;
            }

            base.Draw();
        }

        private void Rebuild(TreeViewItem item, int indentCount = 0)
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

                foreach (TreeViewItem child in item.Children)
                    Rebuild(child, indentCount);
            }
        }

        private void SetAllChildrenVisibuilty(TreeViewItem item, bool visible)
        {
            foreach (TreeViewItem child in item.Children)
            {
                child.Visible = visible;
                SetAllChildrenVisibuilty(child, visible);
            }
        }
    }
}
