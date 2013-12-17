using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ContextComponent : VerticalContainer
    {
        public ContextComponentHeader Header;
        public VerticalContainer Content;

        public ContextComponent(String name)
        {
            Header = new ContextComponentHeader(this, name);
            base.AddControl(Header);
            Header.Width = 50;

            Content = new VerticalContainer();
            base.AddControl(Content);
            Content.Width = 50;

            //Header.ExpansionButton.OnExpand += (s, a) => { Content.Visible = true; Content.Rebuild(); };
            //Header.ExpansionButton.OnCollapse += (s, a) => { Content.Visible = false; Content.Rebuild(); };
        }

    }
}
