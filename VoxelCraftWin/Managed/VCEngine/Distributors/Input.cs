using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public enum MouseMoveMode
    {
        Free,
        Locked
    }

    public static class Input
    {
		
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropInputGetMouse(out float x, out float y, out bool left, out bool right);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropInputSetMouse(float x, float y);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static bool VCInteropInputGetKey(int key);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropInputSetCursorVisible(bool val);

        public static bool Fire;
        public static bool AltFire;

        public static MouseMoveMode MouseMode = MouseMoveMode.Locked;

        private static float m_deltaMouseX;
        private static float m_deltaMouseY;

        private static float m_lastMouseX;
        private static float m_lastMouseY;

        public static Vector3 Look 
        { 
            get 
            { 
                return new Vector3(m_deltaMouseX, m_deltaMouseY, 0.0f); 
            } 
        }

        public static Vector2 Strafe
        {
            get
            {
                Vector2 strafeVec = new Vector2(0.0f, 0.0f);

                if ( IsKeyDown('W') ) strafeVec.X += 1.0f;
                if ( IsKeyDown('S') ) strafeVec.X += -1.0f;

                if ( IsKeyDown('A') ) strafeVec.Y += 1.0f;
                if ( IsKeyDown('D') ) strafeVec.Y += -1.0f;

                return strafeVec;
            }
        }

        public static bool IsKeyDown(int keyCode)
        {
            return VCInteropInputGetKey(keyCode);
        }

        internal static void Update()
        {
            float x;
            float y;
            bool left;
            bool right;

            VCInteropInputGetMouse(out x, out y, out left, out right);

            m_deltaMouseX = -(m_lastMouseX - x) / Window.Size.X;
            m_deltaMouseY = -(m_lastMouseY - y) / Window.Size.Y;

            switch (MouseMode)
            {
                case MouseMoveMode.Free:
                    VCInteropInputSetCursorVisible(true);
                    m_lastMouseX = x;
                    m_lastMouseY = y;
                    break;

                case MouseMoveMode.Locked:
                    VCInteropInputSetCursorVisible(false);
                    VCInteropInputSetMouse(Window.Size.X * 0.5f, Window.Size.Y * 0.5f);
                    m_lastMouseX = Window.Size.X * 0.5f;
                    m_lastMouseY = Window.Size.Y * 0.5f;
                    break;
            }
        }
    }
}
