using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TreeViewItem : Control
    {
        public List<TreeViewItem> Children = new List<TreeViewItem>();
        public Boolean IsExpanded { get { return m_expButton.IsExpanded; } }
        public int IndentationSize = 30;
        public int IndentationCount
        {
            get { return m_indentCount; }
            set
            {
                if (value == m_indentCount)
                    return;

                m_indentCount = value;
                m_expButton.Frame = new Rectangle(IndentationSize * value, 3, 8, 8);
            }
        }
        public string Text;
        public Object BoundObject;

        private TreeView m_treeView;
        private TreeViewItem m_parentItem;
        private ExpandButton m_expButton;
        private int m_indentCount;

        public TreeViewItem(TreeView treeView, TreeViewItem parentItem)
        {
            m_treeView = treeView;
            m_parentItem = parentItem;

            Frame = new Rectangle(0, 0, 100, 15);
            CanFocus = true;

            m_expButton = new ExpandButton();
            m_expButton.IsExpanded = false;
            m_expButton.Frame = new Rectangle(IndentationSize * IndentationCount, 4, 8, 8);

            m_expButton.OnExpand += (s, a) => m_treeView.NotfyUpdate();
            m_expButton.OnCollapse += (s, a) => m_treeView.NotfyUpdate();

            AddControl(m_expButton);
        }

        public void AddChildItem(TreeViewItem item)
        {
            m_treeView.AddControl(item);
            Children.Add(item);
            m_treeView.NotfyUpdate();
        }

        protected override void Draw()
        {
            base.Draw();

            Rectangle sf = ScreenFrame;
            Gui.DrawString(Text, new Point(sf.X + IndentationSize * IndentationCount + 15, sf.Y), Color.Black);

            // ToDo draw selection.
            if (Children.Count == 0)
                m_expButton.Visible = false;
        }
        
    }
}
