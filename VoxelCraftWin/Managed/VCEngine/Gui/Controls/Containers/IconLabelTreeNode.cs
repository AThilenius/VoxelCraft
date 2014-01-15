using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class IconLabelTreeNode : TreeNode
    {
        public override bool IsExpanded { get { return ExpandButton.IsExpanded; } }
        public override bool IsLeaf { get { return !ExpandButton.Visible; } }
        public ExpandButton ExpandButton;
        public ImageView Icon;
        public Label Label;

        public IconLabelTreeNode(String label)
        {
            // Expand Button
            ExpandButton = new VCEngine.ExpandButton();
            ExpandButton.OnExpand += (s, a) => Expand();
            ExpandButton.OnCollapse += (s, a) => Collapse();
            base.AddControl(ExpandButton);

            // Label
            Label = new VCEngine.Label(label);
            Label.TextAlignment = VCEngine.Label.TextAlignments.CenterLeft;
            Label.IsEventPassthrough = true;
            base.AddControl(Label);

            //Image
            Icon = new ImageView();
            Icon.ImagePath = @"Icons\Folder 128.DDS"; ;
            Icon.IsEventPassthrough = true;
            base.AddControl(Icon);

            DoubleClick += (s, a) =>
                {
                    if (ExpandButton.Visible)
                        ExpandButton.ToggleExpandContract();
                };
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

        protected int m_indentSize = 10;

        protected override void ReBuildLayout()
        {
 	         base.ReBuildLayout();

             int baseIndent = (m_indentSize * m_depth) + 5;
             ExpandButton.Frame = new Rectangle(baseIndent, Height - ClientHeight + (ClientHeight / 2) - 4, 8, 8);
             Icon.Frame = new Rectangle(baseIndent + 12, Height - ClientHeight + (ClientHeight / 2) - 10, 20, 20);
             Label.Frame = new Rectangle(baseIndent + 35, Height - ClientHeight + 0, Width - (baseIndent + 40), ClientHeight);

             ExpandButton.Visible = m_childrenLTI.Count != 0;
        }

        protected override void Draw()
        {
            if ( FocusLevel == NodeFocusLevel.ActiveClicked )
                Gui.DrawButtonHighlighted(ClientScreenFrame);

            else if (FocusLevel == NodeFocusLevel.InActiveClicked)
                Gui.DrawButtonAccentuated(ClientScreenFrame);

            Label.FontColor = (FocusLevel == NodeFocusLevel.ActiveClicked) ? Color.White : Color.Black;
        }
    }
}
