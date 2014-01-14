using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// Allows for data binding and viewing of an arbitrarily complex tree of TRANSPARENT Controls.
    /// All controls will have a uniform size enforced.
    /// This view does not inherently support scrolling, or clipping of too many items.
    /// </summary>
    public class TreeView<T> : Control where T : ObservableTreeNode
    {
        public T HeadNode
        {
            get { return m_head; }
            set 
            {
                if (m_head != null)
                    RemoveControl(m_head);

                m_head = value;
                AddControl(value);
                ReBuildList();
            }
        }
        public int ItemHeight
        {
            get { return m_itemHeight; }
            set
            {
                m_itemHeight = value;
                ReBuildList();
            }
        }
        public Boolean HotTracking = true;

        private T m_head;
        private int m_itemHeight = 25;

        // Used during a rebuild
        private List<Control> m_visibleControls = new List<Control>();

        public void ReBuildList()
        {
            int yOffset = m_itemHeight;
            m_visibleControls.Clear();
            BuildVisibuilityListDepthFirst(m_head);

            Rectangle sf = ScreenFrame;
            int newHeight = m_itemHeight * m_visibleControls.Count;
            Size = new Point(Width, newHeight);

            for (int i = 0; i < m_visibleControls.Count; i++)
            {
                m_visibleControls[i].ScreenFrame = new Rectangle(sf.X, sf.Y + newHeight - yOffset, Width, m_itemHeight);
                yOffset += m_itemHeight;
            }

        }

        private void BuildVisibuilityListDepthFirst(Control ctrl)
        {
            if (!ctrl.Visible || !(ctrl is T))
                return;

            m_visibleControls.Add(ctrl);

            for (int i = 0; i < ctrl.Children.Count; i++)
                BuildVisibuilityListDepthFirst(ctrl.Children[i]);
        }

        protected override void Draw()
        {
            //Gui.DrawBackground(ScreenFrame);
        }

    }
}
