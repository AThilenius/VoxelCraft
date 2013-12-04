using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorWorld
    {
        internal static GameWindow MasterGameWindow;

        internal static void Initialize()
        {
            //MasterGameWindow = new GameWindow(2);
            //Control.MainControl.AddControl(MasterGameWindow);
            //MasterGameWindow.Frame = new Rectangle(0, 0, Window.FullViewport.Width - 300, Window.FullViewport.Height - 20);
            //Window.Resize += (s, a) => MasterGameWindow.Frame = new Rectangle(0, 0, Window.FullViewport.Width - 300, Window.FullViewport.Height - 20);
        }
    }
}
