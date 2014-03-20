using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ToolContextComponent : Control, IContextComponent
    {
        public event EventHandler OnExpand;
        public event EventHandler OnCollapse;

        public bool HasHeader { get { return true; } }
        public bool IsExpanded { get { return ToolHeader.ExpansionButton.IsExpanded; } }
        public Control Header { get { return ToolHeader; } }
        public Control Body { get { return this; } }
        public ToolContextComponentHeader ToolHeader;

        public ToolContextComponent(Window window, String name) : base(window)
        {
            // Create tool header
            ToolHeader = new ToolContextComponentHeader(ParentWindow, this, name);
            ToolHeader.Dock = Dockings.Top;
            ToolHeader.Height = 20;

            // Forward Events to IContextComponent
            ToolHeader.ExpansionButton.OnExpand += (s, a) => OnExpand(s, a);
            ToolHeader.ExpansionButton.OnCollapse += (s, a) => OnCollapse(s, a);

            // DO NOT ADD CONTROL
        }
    }
}
