using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ToolContextComponentHeader : Control
    {
        public ExpandButton ExpansionButton;
        public Label Text;

        protected ToolContextComponent m_context;

        public ToolContextComponentHeader(Window window, ToolContextComponent context, String name) : base(window)
        {
            m_context = context;

            ExpansionButton = new ExpandButton(ParentWindow);
            AddControl(ExpansionButton);
            ExpansionButton.IsExpanded = true;
            ExpansionButton.Frame = new Rectangle(5, 6, 8, 8);
            ExpansionButton.BackgroundColor = new Color(112, 126, 140, 255);

            Text = new Label(ParentWindow, name);
            AddControl(Text);
            Text.Dock = Dockings.Fill;
            Text.IsEventPassthrough = true;

            DoubleClick += (s, a) => ExpansionButton.ToggleExpandContract();
        }

        protected override void Draw()
        {
            GuiDrawer.DrawButtonAccentuated(ScreenFrame);
        }

    }
}
