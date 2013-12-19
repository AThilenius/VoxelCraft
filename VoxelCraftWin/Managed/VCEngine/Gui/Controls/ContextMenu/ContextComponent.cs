using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ContextComponent : Control
    {
        public ContextComponentHeader Header;

        public ContextComponent(String name)
        {
            Header = new ContextComponentHeader(this, name);
            Header.Dock = Dockings.Top;
            Header.Height = 20;
            // DO NOT ADD CONTROL
        }

    }
}
