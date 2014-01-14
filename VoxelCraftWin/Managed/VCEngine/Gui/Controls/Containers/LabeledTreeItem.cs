using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// FIX: This control needs to expand out to encompass all its children.
    /// This is needed for Chain-Of-Command traversal (woops).
    /// Move that behaver into TreeNode base class, dump ObservableTreeNode.
    /// Also, remove the constraint on nodes that they must be the same size,
    /// then I can add in large header nodes.
    /// </summary>
    public class TreeNode : Control
    {
        public ExpandButton ExpandButton;
        public ImageView Icon;
        public Label Label;
        public int ClientYOffset;
        public Rectangle ClientScreenFrame
        {
            get { return new Rectangle(ScreenFrame.X, ScreenFrame.Y + ClientYOffset, Width, Height - ClientYOffset); }
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
        public int IndentSize
        {
            get { return m_indentSize; }
            set
            {
                m_indentSize = value;
                ReBuildLayout();
            }
        }

        private int m_depth;
        private int m_indentSize = 10;
        private List<TreeNode> m_childrenLTI = new List<TreeNode>();
        private Point m_lastSize = new Point();

        public TreeNode(String label)
        {
            // Expand Button
            ExpandButton = new VCEngine.ExpandButton();
            ExpandButton.OnExpand += (s, a) =>
                {
                    for (int i = 0; i < m_childrenLTI.Count; i++)
                        m_childrenLTI[i].Visible = true;

                    ReBuildLayout();
                };
            ExpandButton.OnCollapse += (s, a) =>
                {
                    for (int i = 0; i < m_childrenLTI.Count; i++)
                        m_childrenLTI[i].Visible = false;

                    ReBuildLayout();
                };
            ExpandButton.IsExpanded = true;
            base.AddControl(ExpandButton);

            // Label
            Label = new VCEngine.Label(label);
            Label.TextAlignment = VCEngine.Label.TextAlignments.CenterLeft;
            base.AddControl(Label);

            //Image
            Icon = new ImageView();
            Icon.ImagePath = @"Icons\Folder 128.DDS"; ;
            base.AddControl(Icon);

            ReBuildLayout();
            Resize += (s, a) => ReBuildLayout();
        }

        public override void AddControl(Control control)
        {
            if (!(control is TreeNode))
                throw new NotSupportedException("You can only add LabeledTreeItem controls as children of a LabeledTreeItem");

            base.AddControl(control);
            m_childrenLTI.Add((TreeNode)control);
            ((TreeNode)control).Depth = Depth + 1;
        }

        public override void RemoveControl(Control control)
        {
            base.RemoveControl(control);
            ((TreeNode)control).Depth = 0;
            m_childrenLTI.Remove((TreeNode)control);
        }

        protected virtual void ReBuildLayout()
        {
            // For each child, let it first compute its layout,
            // align in this frame, set size to sum
            int runningYOffset = 0;

            for (int i = m_childrenLTI.Count - 1; i >= 0; i--)
            {
                TreeNode node = m_childrenLTI[i];

                // Depth First
                node.ReBuildLayout();
                node.Frame = new Rectangle(0, runningYOffset, Width, node.Height);
                runningYOffset += node.Height;
            }

            Height = runningYOffset;
        }

        //if (Size.X == m_lastSize.X && Size.Y == m_lastSize.Y)
        //        return;

        //    m_lastSize = Size;
        //    int baseIndent = (m_indentSize * m_depth) + 5;
        //    ExpandButton.Frame =    new Rectangle(baseIndent,      (Height / 2) - 4,   8,                             8);
        //    Icon.Frame =            new Rectangle(baseIndent + 12, (Height / 2) - 10,                  20,                        20);
        //    Label.Frame =           new Rectangle(baseIndent + 35, 0,                  Width - (baseIndent + 40),    Height);

        //    if (m_childrenLTI.Count == 0)
        //        ExpandButton.Visible = false;

        protected override void Draw()
        {
            Gui.DrawButton(ScreenFrame);
        }

    }
}
