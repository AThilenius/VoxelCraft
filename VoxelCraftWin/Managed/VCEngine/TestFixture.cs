using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TestFixture
    {

        internal static void OnStart()
        {

        }

        public static void PerUpdate()
        {
        }

        public static void LatePerUpdate()
        {
            Rectangle testFrame = new Rectangle(200, Window.ScaledSize.Y - 60, 150, 60);
            Gui.Draw9Slice(@"Icons\Button.DDS", testFrame);
        }


    }
}
