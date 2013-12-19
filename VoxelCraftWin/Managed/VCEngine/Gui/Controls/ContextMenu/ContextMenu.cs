using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ContextMenu : Control
    {
        private List<ContextComponent> m_orderedControlList = new List<ContextComponent>();

        public override void AddControl(Control control)
        {
            ContextComponent cc = (ContextComponent)control;

            if (cc == null)
                throw  new Exception("Only ContextComponents or derived classes can be added to a ContextMenu");

            cc.Dock = Dockings.Top;
            m_orderedControlList.Add(cc);
            cc.Header.ExpansionButton.OnExpand += (s, a) => ReBuild();
            cc.Header.ExpansionButton.OnCollapse += (s, a) => ReBuild();

            ReBuild();
        }

        public void ReBuild()
        {
            base.RemoveAllControls();
            int yOffset = 0;

            foreach (ContextComponent cc in m_orderedControlList)
            {
                cc.Header.DockOrder = yOffset++;
                base.AddControl(cc.Header);

                if (cc.Header.ExpansionButton.IsExpanded)
                {
                    cc.DockOrder = yOffset++;
                    base.AddControl(cc);
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
