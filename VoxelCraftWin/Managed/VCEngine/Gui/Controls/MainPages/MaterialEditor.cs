using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialEditor : Control
    {
        public ContextMenu FilesContextMenu;

        public MaterialEditor()
        {
            FilesContextMenu = new ContextMenu();
            AddControl(FilesContextMenu);
            //FilesContextMenu.Dock = Dockings.Left;
            FilesContextMenu.Frame = new Rectangle(0, 0, 250, Window.ScaledSize.Y - 75);
        }

        protected override void Draw()
        {
            Gui.DrawBorderedRect(ScreenFrame, Color.ControlDark, Color.ControlRed, 5);
        }

    }
}
