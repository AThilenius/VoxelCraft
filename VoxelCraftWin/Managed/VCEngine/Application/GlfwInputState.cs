﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public static class GlfwInputState
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropInputSetMouse(float x, float y);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropInputSetCursorVisible(bool val);


        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwKeyUnmanagedDelegate(int key, int scancode, int action, int mods);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwCharUnmanagedDelegate(uint charCode);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwMouseMoveUnmanagedDelegate(double x, double y);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwMouseClickUnmanagedDelegate(int button, int action, int mods);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwMouseEnterUnmanagedDelegate(int entered);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwMouseScrollUnmanagedDelegate(double xOffset, double yOffset);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropInputSetCallbacks( GlfwKeyUnmanagedDelegate keyCallback,
                                                       GlfwCharUnmanagedDelegate charCallback,
                                                       GlfwMouseMoveUnmanagedDelegate mouseMoveCallback,
                                                       GlfwMouseClickUnmanagedDelegate mouseClickCallback,
                                                       GlfwMouseEnterUnmanagedDelegate mouseEnterCallback,
                                                       GlfwMouseScrollUnmanagedDelegate mouseScrollCallback);

        #endregion

        // Events
        public static event EventHandler OnScrollChange = delegate { };
        public static event EventHandler OnFocusChange = delegate { };
        public static event EventHandler OnMouseMove = delegate { };
        public static event EventHandler<MouseClickEventArgs> OnMouseClick = delegate { };
        public static event EventHandler<KeyEventArgs> OnKey = delegate { };
        public static event EventHandler<CharEventArgs> OnCharClicked = delegate { };

        // States
        public static Point PreviouseMouseLocation = new Point();
        public static Point DeltaMouseLocation = new Point();
        public static Point MouseLocation
        {
            get { return m_currentMousePosition; }
            set
            {
                // Overwrite previous to avoid stale spinning
                PreviouseMouseLocation = value;
                m_currentMousePosition = value;
                VCInteropInputSetMouse((int) Math.Round(value.X * Gui.Scale), (int) Math.Round((Window.ScaledSize.Y - value.Y) * Gui.Scale));
            }
        }
        public static Point InvertedMouseLocation
        {
            get { return new Point(m_currentMousePosition.X, Window.ScaledSize.Y - m_currentMousePosition.Y); }
            set
            {
                // Overwrite previous to avoid stale spinning
                PreviouseMouseLocation = value;
                m_currentMousePosition = value;
                VCInteropInputSetMouse((int) Math.Round(value.X * Gui.Scale), (int) Math.Round(value.Y * Gui.Scale));
            }
        }
        public static PointF DeltaScroll = new PointF();
        public static Boolean MouseVisible
        {
            get { return m_mouseVisible; }
            set
            {
                m_mouseVisible = value;
                VCInteropInputSetCursorVisible(value);
            }
        }
        public static Boolean Focused { get; private set; }
        public static TrinaryStateTracker[] MouseStates = new TrinaryStateTracker[10];
        public static TrinaryStateTracker[] KeyStates = new TrinaryStateTracker[350];
        public static int KeysDown;

        private static Point m_currentMousePosition = new Point();
        private static Boolean m_mouseVisible = true;

        public static void Initialize()
        {
            VCInteropInputSetCallbacks(
                (key, scancode, action, mods) => GlfwKeyCallback(key, scancode, action, mods),
                (charCode) => GlfwCharCallback(charCode),
                (x, y) => GlfwMouseMoveCallback(x, y),
                (button, action, mods) => GlfwMouseClickCallback(button, action, mods),
                (entered) => GlfwMouseEnterCallback(entered),
                (xOffset, yOffset) => GlfwMouseScrollCallback(xOffset, yOffset));
        }

        internal static void StepStates()
        {
            DeltaMouseLocation = new Point(0, 0);

            for (int i = 0; i < 10; i++)
                MouseStates[i].StepState();

            for (int i = 0; i < 350; i++)
                KeyStates[i].StepState();
        }

        // Callbacks
        private static void GlfwKeyCallback(int key, int scancode, int action, int mods)
        {
            if (action == 0)
                KeysDown--;

            if (action == 1)
                KeysDown++;

            Editor.ShouldRedraw();
            KeyStates[key].Update(action > 0);
            OnKey(null, new KeyEventArgs { Key = key });
        }

        private static void GlfwCharCallback(uint charCode)
        {
            Editor.ShouldRedraw();
            OnCharClicked(null, new CharEventArgs { Char = (int)charCode });
        }

        private static void GlfwMouseMoveCallback(double x, double y)
        {
            Editor.ShouldRedraw();

            // Scale
            x /= Gui.Scale;
            y /= Gui.Scale;

            PreviouseMouseLocation = m_currentMousePosition;
            m_currentMousePosition = new Point((int)x, Window.ScaledSize.Y - (int)y);
            DeltaMouseLocation = new Point(-(PreviouseMouseLocation.X - m_currentMousePosition.X), -(PreviouseMouseLocation.Y - m_currentMousePosition.Y));
            OnMouseMove(null, EventArgs.Empty  );
        }

        private static void GlfwMouseClickCallback(int button, int action, int mods)
        {
            Editor.ShouldRedraw();
            MouseStates[button].Update(action > 0);
            OnMouseClick(null, new MouseClickEventArgs { Button = button });
        }

        private static void GlfwMouseEnterCallback(int entered)
        {
            Editor.ShouldRedraw();
            Focused = entered > 0;
            OnFocusChange(null, EventArgs.Empty);
        }

        private static void GlfwMouseScrollCallback(double xOffset, double yOffset)
        {
            Editor.ShouldRedraw();
            DeltaScroll = new PointF((float)xOffset, (float)yOffset);
            OnScrollChange(null, EventArgs.Empty);
        }
    }
}
