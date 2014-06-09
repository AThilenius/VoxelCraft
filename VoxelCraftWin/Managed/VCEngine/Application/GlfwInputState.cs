using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class GlfwInputState
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropInputSetMouse(int windowHandle, float x, float y);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropInputSetCursorVisible(int windowHandle, bool val);


        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwKeyUnmanagedDelegate(int windowHandle, int key, int scancode, int action, int mods);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwCharUnmanagedDelegate(int windowHandle, uint charCode);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwMouseMoveUnmanagedDelegate(int windowHandle, double x, double y);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwMouseClickUnmanagedDelegate(int windowHandle, int button, int action, int mods);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwMouseEnterUnmanagedDelegate(int windowHandle, int entered);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwMouseScrollUnmanagedDelegate(int windowHandle, double xOffset, double yOffset);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropInputSetCallbacks( GlfwKeyUnmanagedDelegate keyCallback,
                                                       GlfwCharUnmanagedDelegate charCallback,
                                                       GlfwMouseMoveUnmanagedDelegate mouseMoveCallback,
                                                       GlfwMouseClickUnmanagedDelegate mouseClickCallback,
                                                       GlfwMouseEnterUnmanagedDelegate mouseEnterCallback,
                                                       GlfwMouseScrollUnmanagedDelegate mouseScrollCallback);

        #endregion

        // Events
        public event EventHandler OnScrollChange = delegate { };
        public event EventHandler OnFocusChange = delegate { };
        public event EventHandler OnMouseMove = delegate { };
        public event EventHandler<MouseClickEventArgs> OnMouseClick = delegate { };
        public event EventHandler<KeyEventArgs> OnKey = delegate { };
        public event EventHandler<CharEventArgs> OnCharClicked = delegate { };

        // States
        public Point PreviouseMouseLocation = new Point();
        public Point DeltaMouseLocation = new Point();
        public Point MouseLocation
        {
            get { return m_currentMousePosition; }
            set
            {
                // Overwrite previous to avoid stale spinning
                PreviouseMouseLocation = value;
                m_currentMousePosition = value;
                VCInteropInputSetMouse(ParentWindow.UnManagedHandle, (int)Math.Round(value.X * ParentWindow.Gui.Scale), (int)Math.Round((ParentWindow.ScaledSize.Y - value.Y) * ParentWindow.Gui.Scale));
            }
        }
        public Point InvertedMouseLocation
        {
            get { return new Point(m_currentMousePosition.X, ParentWindow.ScaledSize.Y - m_currentMousePosition.Y); }
            set
            {
                // Overwrite previous to avoid stale spinning
                PreviouseMouseLocation = value;
                m_currentMousePosition = value;
                VCInteropInputSetMouse(ParentWindow.UnManagedHandle, (int)Math.Round(value.X * ParentWindow.Gui.Scale), (int)Math.Round(value.Y * ParentWindow.Gui.Scale));
            }
        }
        public PointF DeltaScroll = new PointF();
        public Boolean MouseVisible
        {
            get { return m_mouseVisible; }
            set
            {
                m_mouseVisible = value;
                VCInteropInputSetCursorVisible(ParentWindow.UnManagedHandle, value);
            }
        }
        public Boolean Focused { get; private set; }
        public TrinaryStateTracker[] MouseStates = new TrinaryStateTracker[10];
        public TrinaryStateTracker[] KeyStates = new TrinaryStateTracker[350];
        public int KeysDown;
        public Input Input;
        public Window ParentWindow;

        private Point m_currentMousePosition = new Point();
        private Boolean m_mouseVisible = true;

        public GlfwInputState(Window window, Input input)
        {
            Input = input;
            ParentWindow = window;

            VCInteropInputSetCallbacks(
                (winHandle, key, scancode, action, mods) => GlfwKeyCallback(winHandle, key, scancode, action, mods),
                (winHandle, charCode) => GlfwCharCallback(winHandle, charCode),
                (winHandle, x, y) => GlfwMouseMoveCallback(winHandle, x, y),
                (winHandle, button, action, mods) => GlfwMouseClickCallback(winHandle, button, action, mods),
                (winHandle, entered) => GlfwMouseEnterCallback(winHandle, entered),
                (winHandle, xOffset, yOffset) => GlfwMouseScrollCallback(winHandle, xOffset, yOffset));
        }

        internal void StepStates()
        {
            DeltaMouseLocation = new Point(0, 0);
            DeltaScroll = new PointF(0, 0);

            for (int i = 0; i < 10; i++)
                MouseStates[i].StepState();

            for (int i = 0; i < 350; i++)
                KeyStates[i].StepState();
        }

        #region Callbacks

        private static void GlfwKeyCallback(int windowHandle, int key, int scancode, int action, int mods)
        {
            Window win = ObjectStore.GetObject(windowHandle) as Window;

            if (action == 0)
                win.GlfwInputState.KeysDown--;

            if (action == 1)
                win.GlfwInputState.KeysDown++;

            win.ShouldRedraw();
            win.GlfwInputState.KeyStates[key].Update(action > 0);
            win.GlfwInputState.OnKey(null, new KeyEventArgs(win, key));
        }

        private static void GlfwCharCallback(int windowHandle, uint charCode)
        {
            Window win = ObjectStore.GetObject(windowHandle) as Window;

            win.ShouldRedraw();
            win.GlfwInputState.OnCharClicked(null, new CharEventArgs(win, (int)charCode));
        }

        private static void GlfwMouseMoveCallback(int windowHandle, double x, double y)
        {
            Window win = ObjectStore.GetObject(windowHandle) as Window;

            if (win == null)
                return;

            win.ShouldRedraw();

            // Scale
            x /= win.Gui.Scale;
            y /= win.Gui.Scale;

            win.GlfwInputState.PreviouseMouseLocation = win.GlfwInputState.m_currentMousePosition;
            win.GlfwInputState.m_currentMousePosition = new Point((int)x, win.ScaledSize.Y - (int)y);
            win.GlfwInputState.DeltaMouseLocation = new Point(
                -(win.GlfwInputState.PreviouseMouseLocation.X - win.GlfwInputState.m_currentMousePosition.X), 
                -(win.GlfwInputState.PreviouseMouseLocation.Y - win.GlfwInputState.m_currentMousePosition.Y));
            win.GlfwInputState.OnMouseMove(null, EventArgs.Empty);
        }

        private static void GlfwMouseClickCallback(int windowHandle, int button, int action, int mods)
        {
            Window win = ObjectStore.GetObject(windowHandle) as Window;

            win.ShouldRedraw();
            win.GlfwInputState.MouseStates[button].Update(action > 0);
            win.GlfwInputState.OnMouseClick(null, new MouseClickEventArgs(win, button));
        }

        private static void GlfwMouseEnterCallback(int windowHandle, int entered)
        {
            Window win = ObjectStore.GetObject(windowHandle) as Window;

            win.ShouldRedraw();
            win.GlfwInputState.Focused = entered > 0;
            win.GlfwInputState.OnFocusChange(null, EventArgs.Empty);
        }

        private static void GlfwMouseScrollCallback(int windowHandle, double xOffset, double yOffset)
        {
            Window win = ObjectStore.GetObject(windowHandle) as Window;

            win.ShouldRedraw();
            win.GlfwInputState.DeltaScroll = new PointF((float)xOffset, (float)yOffset);
            win.GlfwInputState.OnScrollChange(null, EventArgs.Empty);
        }

        #endregion
    }
}
