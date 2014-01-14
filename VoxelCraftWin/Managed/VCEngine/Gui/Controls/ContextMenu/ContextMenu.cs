using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ContextMenu : Control
    {
        private List<IContextComponent> m_orderedControlList = new List<IContextComponent>();

        public void AddIContextComponent(IContextComponent iContextCompoennt)
        {
            iContextCompoennt.Body.Dock = Dockings.Top;
            m_orderedControlList.Add(iContextCompoennt);

            iContextCompoennt.OnExpand += (s, a) => ReBuild();
            iContextCompoennt.OnCollapse += (s, a) => ReBuild();

            ReBuild();
        }

        public override void AddControl(Control control)
        {
            throw new NotSupportedException ("Must use AddIContextComponent instead");
        }

        public void ReBuild()
        {
            base.RemoveAllControls();
            int yOffset = 0;

            foreach (IContextComponent cc in m_orderedControlList)
            {
                if (cc.HasHeader)
                {
                    cc.Header.DockOrder = yOffset++;
                    base.AddControl(cc.Header);
                }

                if (cc.IsExpanded)
                {
                    cc.Body.DockOrder = yOffset++;
                    base.AddControl(cc.Body);
                }
            }

            RefreshDocks();
        }

        protected override void Draw()
        {
            Gui.DrawBackgroundEmpty(ScreenFrame, false);
        }

    }
}
