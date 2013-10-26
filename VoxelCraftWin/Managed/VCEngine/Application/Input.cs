using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    #region Enums, Args, Helpers
    public enum MouseMoveMode
    {
        Free,
        Locked
    }

    [Flags]
    public enum KeyModFlags : short
    {
        Shift = 0x0001,
        Ctrl = 0x0002,
        Alt = 0x0004,
        Super = 0x0008
    }

    public struct KeyState
    {
        public int Key;
        public TriState Action;
        public KeyModFlags Modifiers;

        public bool Shift { get { return (Modifiers & KeyModFlags.Shift) == KeyModFlags.Shift; } }
        public bool Ctrl { get { return (Modifiers & KeyModFlags.Ctrl) == KeyModFlags.Ctrl; } }
        public bool Alt { get { return (Modifiers & KeyModFlags.Alt) == KeyModFlags.Alt; } }
        public bool Super { get { return (Modifiers & KeyModFlags.Super) == KeyModFlags.Super; } }

        public KeyState(int key, TriState action, int mods)
        {
            Key = key;
            Action = action;
            Modifiers = (KeyModFlags)(short) mods;
        }

    }

    public class KeyEventArgs : EventArgs
    {
        public KeyState State;
    }

    public class CharEventArgs : EventArgs
    {
        public int CharCode;
    }

    public class MouseMoveEventArgs : EventArgs
    {
        public Point ScreenLocation;
        public Point DeltaLocation;
    }

    public class MouseClickEventArgs : EventArgs
    {
        public enum MouseButton : int
        {
            Left = 0,
            Right = 1
        }

        public MouseButton Button;
        public TriState Action;
        public KeyModFlags Modifiers;
        public Point ScreenLocation;

        public bool Shift { get { return (Modifiers & KeyModFlags.Shift) == KeyModFlags.Shift; } }
        public bool Ctrl { get { return (Modifiers & KeyModFlags.Ctrl) == KeyModFlags.Ctrl; } }
        public bool Alt { get { return (Modifiers & KeyModFlags.Alt) == KeyModFlags.Alt; } }
        public bool Super { get { return (Modifiers & KeyModFlags.Super) == KeyModFlags.Super; } }

    }

    public class FocusEventArgs : EventArgs
    {
        public enum ForcusAction : int
        {
            Exited = 0,
            Entered = 1
        }

        public ForcusAction Action;
        public Point ScreenLocation;
    }

    public class MouseScrollEventArgs : EventArgs
    {
        public PointF Offset;
        public Point ScreenLocation;
    }


    #endregion

    public static class Input
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropInputGetMouse(out float x, out float y);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropInputSetMouse(float x, float y);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropInputSetCursorVisible(bool val);

        #endregion

        #region Keys
        public struct Keys
        {
            public const int Escape = 256;
            public const int Enter = 257;
            public const int Tab = 258;
            public const int Backspace = 259;
            public const int Insert = 260;
            public const int Delete = 261;
            public const int Right = 262;
            public const int Left = 263;
            public const int Down = 264;
            public const int Up = 265;
            public const int PageUp = 266;
            public const int PageDown = 267;
            public const int Home = 268;
            public const int End = 269;
            public const int CapsLock = 280;
            public const int ScrollLock = 281;
            public const int NumLock = 282;
            public const int PrintScreen = 283;
            public const int Pause = 284;
            public const int F1 = 290;
            public const int F2 = 291;
            public const int F3 = 292;
            public const int F4 = 293;
            public const int F5 = 294;
            public const int F6 = 295;
            public const int F7 = 296;
            public const int F8 = 297;
            public const int F9 = 298;
            public const int F10 = 299;
            public const int F11 = 300;
            public const int F12 = 301;
            public const int F13 = 302;
            public const int F14 = 303;
            public const int F15 = 304;
            public const int F16 = 305;
            public const int F17 = 306;
            public const int F18 = 307;
            public const int F19 = 308;
            public const int F20 = 309;
            public const int F21 = 310;
            public const int F22 = 311;
            public const int F23 = 312;
            public const int F24 = 313;
            public const int F25 = 314;
            public const int Kp0 = 320;
            public const int Kp1 = 321;
            public const int Kp2 = 322;
            public const int Kp3 = 323;
            public const int Kp4 = 324;
            public const int Kp5 = 325;
            public const int Kp6 = 326;
            public const int Kp7 = 327;
            public const int Kp8 = 328;
            public const int Kp9 = 329;
            public const int KpDecimal = 330;
            public const int KpDivide = 331;
            public const int KpMultiply = 332;
            public const int KpSubtract = 333;
            public const int KpAdd = 334;
            public const int KpEnter = 335;
            public const int KpEqual = 336;
            public const int LeftShift = 340;
            public const int LeftControl = 341;
            public const int LeftAlt = 342;
            public const int LeftSuper = 343;
            public const int RightShift = 344;
            public const int RightControl = 345;
            public const int RightAlt = 346;
            public const int RightSuper = 347;
            public const int Menu = 348;
        }
        #endregion

        #region Events
        public static event EventHandler<KeyEventArgs> KeyClicked = delegate { };
        public static event EventHandler<CharEventArgs> CharClicked = delegate { };
        public static event EventHandler<MouseMoveEventArgs> MouseMove = delegate { };
        public static event EventHandler<MouseClickEventArgs> MouseClick = delegate { };
        public static event EventHandler<MouseScrollEventArgs> MouseScroll = delegate { };
        public static event EventHandler<FocusEventArgs> Focus = delegate { };
        #endregion

        private static MouseMoveMode m_mouseMode = MouseMoveMode.Free;
        public static MouseMoveMode MouseMode
        {
            get { return m_mouseMode; }
            set
            {
                if (value == m_mouseMode)
                    return;

                switch (value)
                {
                    case MouseMoveMode.Free:
                        VCInteropInputSetCursorVisible(true);
                        break;

                    case MouseMoveMode.Locked:
                        VCInteropInputSetCursorVisible(false);
                        break;
                }

                m_mouseMode = value;
            }
        }
        public static Point MousePoistion
        {
            get { return m_lastMousePosition; }
            set
            {
                m_lastMousePosition = value;
                VCInteropInputSetMouse(value.X, Window.Size.Y - value.Y);
            }
        }
        public static Vector2 DeltaLook 
        { 
            get 
            {
                if (m_isSupressingUpdate)
                    return new Vector2(0.0f, 0.0f);

                return new Vector2(m_deltaMousePosition.X, m_deltaMousePosition.Y);
            } 
        }
        public static Vector2 Strafe
        {
            get
            {
                if (m_isSupressingUpdate)
                    return new Vector2(0.0f, 0.0f);

                Vector2 strafeVec = new Vector2(0.0f, 0.0f);
                
                if (m_keyStates['W'].State != TriState.None) strafeVec.X += 1.0f;
                if (m_keyStates['S'].State != TriState.None) strafeVec.X += -1.0f;

                if (m_keyStates['A'].State != TriState.None) strafeVec.Y += 1.0f;
                if (m_keyStates['D'].State != TriState.None) strafeVec.Y += -1.0f;

                if (strafeVec.X > 0.1f || strafeVec.X < -0.1f || strafeVec.Y > 0.1f || strafeVec.Y < -0.1f )
                    strafeVec.Normalize();

                return strafeVec;
            }
        }

        
        private static Point m_lastMousePosition = new Point();
        private static Point m_deltaMousePosition = new Point();

        private static TrinaryStateTracker[] m_mouseStates = new TrinaryStateTracker[10];
        private static TrinaryStateTracker[] m_keyStates = new TrinaryStateTracker[350];

        private static bool m_isSupressingUpdate;

        public static TriState GetKey(int keyCode)
        {
            if (m_isSupressingUpdate)
                return TriState.None;

            return m_keyStates[keyCode].State;
        }

        public static TriState GetMouse(int button)
        {
            if (m_isSupressingUpdate)
                return TriState.None;

            return m_mouseStates[button].State;
        }

        internal static void Start()
        {
            float x, y;
            VCInteropInputGetMouse(out x, out y);

            m_lastMousePosition = new Point ((int)x, (int)y);
            m_deltaMousePosition = new Point(0, 0);
        }

        internal static void SuppressUpdates()
        {
            m_isSupressingUpdate = true;
        }

        internal static void ActivateUpdates()
        {
            m_isSupressingUpdate = false;
        }

        internal static void ClearStates()
        {
            m_deltaMousePosition = new Point(0, 0);

            for (int i = 0; i < 10; i++)
                m_mouseStates[i].StepState();

            for (int i = 0; i < 350; i++)
                m_keyStates[i].StepState();
        }

        private static void GlfwKeyCallback(int key, int scancode, int action, int mods)
        {
            try
            {
                m_keyStates[key].Update(action > 0);
                KeyClicked(null, new KeyEventArgs { State = new KeyState(key, m_keyStates[key].State, mods) });
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        }

        private static void GlfwCharCallback(int charCode)
        {
            CharClicked(null, new CharEventArgs { CharCode = charCode });
        }

        private static void GlfwMouseMoveCallback(double x, double y)
        {
            try
            {
                Point newLocation = new Point((int)x, Window.Size.Y - (int)y);
                m_deltaMousePosition = new Point ( -(m_lastMousePosition.X - newLocation.X), -(m_lastMousePosition.Y - newLocation.Y));

                switch (MouseMode)
                {
                    case MouseMoveMode.Free:
                        m_lastMousePosition = newLocation;
                        break;

                    case MouseMoveMode.Locked:
                        VCInteropInputSetMouse((int)(Window.Size.X * 0.5f), (int)(Window.Size.Y * 0.5f));
                        m_lastMousePosition = new Point((int)(Window.Size.X * 0.5f), (int)(Window.Size.Y * 0.5f));
                        break;
                }

                MouseMove(null, new MouseMoveEventArgs { ScreenLocation = newLocation, DeltaLocation = m_deltaMousePosition });
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        }

        private static void GlfwMouseClickCallback(int button, int action, int mods)
        {
            try
            {
                m_mouseStates[button].Update(action > 0);

                MouseClick(null, new MouseClickEventArgs
                {
                    Action = m_mouseStates[button].State,
                    Button = (MouseClickEventArgs.MouseButton)button,
                    Modifiers = (KeyModFlags)(short)mods,
                    ScreenLocation = m_lastMousePosition
                });
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        }

        private static void GlfwMouseEnterCallback(int entered)
        {
            try
            {
                Focus(null, new FocusEventArgs { Action = (FocusEventArgs.ForcusAction)entered, ScreenLocation = m_lastMousePosition });
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        }

        private static void GlfwMouseScrollCallback(double xOffset, double yOffset)
        {
            try
            {
                MouseScroll(null, new MouseScrollEventArgs { Offset = new PointF((float)xOffset, (float)yOffset), ScreenLocation = m_lastMousePosition });
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        }
    }
}
