using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class CharEventArgs : EventArgs
    {
        public Window Window;
        public int Char;

        public CharEventArgs(Window window, int character)
        {
            Window = window;
            Char = character;
        }
    }

    public class KeyEventArgs : EventArgs
    {
        public Window Window;
        public int Key;
        public TriState State { get { return Window.GlfwInputState.KeyStates[Key].State; } }

        public KeyEventArgs(Window window, int key)
        {
            Window = window;
            Key = key;
        }
    }

    public class MouseClickEventArgs : EventArgs
    {
        public Window Window;
        public int Button;
        public TriState State { get { return Window.GlfwInputState.MouseStates[Button].State; } }
        public Point Location { get { return Window.GlfwInputState.MouseLocation; } }

        public MouseClickEventArgs(Window window, int button)
        {
            Window = window;
            Button = button;
        }
    }

}