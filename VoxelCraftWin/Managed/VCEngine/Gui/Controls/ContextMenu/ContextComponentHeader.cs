using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ContextComponentHeader : Control
    {
        public ExpandButton ExpansionButton;
        public Label Text;

        protected ContextComponent m_context;

        public ContextComponentHeader(ContextComponent context, String name)
        {
            m_context = context;

            ExpansionButton = new ExpandButton();
            AddControl(ExpansionButton);
            ExpansionButton.IsExpanded = true;
            ExpansionButton.Frame = new Rectangle(5, 6, 8, 8);
            ExpansionButton.BackgroundColor = new Color(112, 126, 140, 255);

            Text = new Label(name);
            AddControl(Text);
            Text.Dock = Dockings.Fill;
            Text.IsEventPassthrough = true;

            DoubleClick += (s, a) => ExpansionButton.ToggleExpandContract();

            Height = 20;
        }

        protected override void Draw()
        {
            //Gui.DrawButtonAccentuated(ScreenFrame);
            Gui.DrawRectangle(ScreenFrame, Color.ControlRed);
        }

    }
}
