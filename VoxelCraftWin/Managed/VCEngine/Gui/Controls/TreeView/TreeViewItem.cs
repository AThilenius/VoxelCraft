using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TreeViewItem : Control
    {
        public List<TreeViewItem> TreeViewChildren = new List<TreeViewItem>();
        public IEnumerable<TreeViewItem> AllChildren
        {
            get
            {
                foreach (TreeViewItem child in TreeViewChildren)
                {
                    yield return child;

                    foreach (TreeViewItem grandchild in child.AllChildren)
                        yield return grandchild;
                }
            }
        }
        public Boolean IsExpanded { get { return m_expButton.IsExpanded; } }
        public Texture Image;
        public int IndentationSize = 15;
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

        private TreeViewOld m_treeView;
        private TreeViewItem m_parentItem;
        private ExpandButton m_expButton;
        private int m_indentCount;

        public TreeViewItem(Window window, TreeViewOld treeView, TreeViewItem parentItem) : base(window)
        {
            m_treeView = treeView;
            m_parentItem = parentItem;

            Frame = new Rectangle(0, 0, 100, 20);
            CanFocus = true;
            Visible = false;

            m_expButton = new ExpandButton(ParentWindow);
            m_expButton.IsExpanded = false;
            m_expButton.Frame = new Rectangle(IndentationSize * IndentationCount + 5, 6, 8, 8);
            m_expButton.BackgroundColor = new Color(112, 126, 140, 255);

            m_expButton.OnExpand += (s, a) => m_treeView.NotifyUpdate();
            m_expButton.OnCollapse += (s, a) => m_treeView.NotifyUpdate();

            AddControl(m_expButton);
        }

        public void ExpandCollapse()
        {
            m_expButton.IsExpanded = !IsExpanded;
            m_treeView.NotifyUpdate();
        }

        public void Collapse()
        {

        }

        public void AddChildItem(TreeViewItem item)
        {
            m_treeView.AddControl(item);
            TreeViewChildren.Add(item);
            m_treeView.NotifyUpdate();
        }

        protected override void Draw()
        {
            // Early out
            if (Frame.Y < 0)
            {
                m_expButton.Visible = false;
                return;
            }

            else
            {
                m_expButton.Visible = true;
                Rectangle sf = ScreenFrame;

                if (IsFocused)
                {
                    Gui.DrawButtonHighlighted(sf);
                    Font.DrawStringBeveled(Text, new Point(sf.X + IndentationSize * IndentationCount + 45, sf.Y + 2), Color.White);
                    m_expButton.BackgroundColor = Color.White;
                    m_expButton.HoverBackgroundColor = Color.White;
                }

                else
                {
                    Font.DrawStringBeveled(Text, new Point(sf.X + IndentationSize * IndentationCount + 45, sf.Y + 2), Color.Black);
                    m_expButton.BackgroundColor = new Color(112, 126, 140, 255);
                    m_expButton.HoverBackgroundColor = Color.ControlBlue;
                }


                // Has Icon?
                if (Image != null)
                    Gui.DrawImage(Image, new Rectangle(sf.X + IndentationSize * IndentationCount + 20, sf.Y, 20, 20));


                if (TreeViewChildren.Count == 0)
                    m_expButton.Visible = false;
            }

        }

    }
}
