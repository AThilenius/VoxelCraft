using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public abstract class MainPageBase : Control
    {
        protected PanelsTrippleButton PanelsTrippleButton;

        public MainPageBase(Window window) : base(window)
        {
            PanelsTrippleButton = new PanelsTrippleButton(ParentWindow);
        }

        public virtual void OnSelected()
        {
            EditorGui.HeaderBar.PanelsButtons = PanelsTrippleButton;
        }

        public virtual void OnDeselected() { }
    }
}
