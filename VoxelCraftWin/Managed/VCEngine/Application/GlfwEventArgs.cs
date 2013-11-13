using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class CharEventArgs : EventArgs
    {
        public int Char;
    }

    public class KeyEventArgs : EventArgs
    {
        public int Key;
        public TriState State { get { return GlfwInputState.KeyStates[Key].State; } }
    }

    public class MouseClickEventArgs : EventArgs
    {
        public int Button;
        public TriState State { get { return GlfwInputState.MouseStates[Button].State; } }
        public Point Location { get { return GlfwInputState.MouseLocation; } }
    }

}