using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public abstract class MainPageBase : Control
    {
        protected PanelsTrippleButton PanelsTrippleButton = new PanelsTrippleButton();

        public virtual void OnSelected()
        {
            EditorGui.HeaderBar.PanelsButtons = PanelsTrippleButton;
        }

        public virtual void OnDeselected() { }
    }
}
