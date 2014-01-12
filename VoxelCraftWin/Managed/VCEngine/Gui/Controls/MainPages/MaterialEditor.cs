using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialEditor : Control
    {

        protected override void Draw()
        {
            Gui.DrawBorderedRect(ScreenFrame, Color.ControlDark, Color.ControlRed, 5);
        }

    }
}
