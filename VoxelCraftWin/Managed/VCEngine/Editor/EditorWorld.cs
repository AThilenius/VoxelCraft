using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorWorld
    {
        internal static GameWindow MasterGameWindow;
        internal static GameWindow SecondaryGameWindow;

        internal static void Initialize()
        {
            MasterGameWindow = new GameWindow(2);
            Control.MainControl.AddControl(MasterGameWindow);
            MasterGameWindow.Frame = Window.FullViewport;

            Window.Resize += (s, a) => MasterGameWindow.Frame = a.To;

            // Test:
            //SecondaryGameWindow = new GameWindow(2);
            //Control.MainControl.AddControl(SecondaryGameWindow);
            //SecondaryGameWindow.Frame = new Rectangle(400, 0, 300, 500);
        }
    }
}
