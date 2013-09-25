using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public static class Input
    {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropInputGetMouse(ref float x, ref float y, ref bool left, ref bool right);
        
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static IntPtr VCInteropInputGetKeys();

        public static bool Fire;
        public static bool AltFire;

        private static float m_deltaMouseX;
        private static float m_deltaMouseY;

        private static float m_lastMouseX;
        private static float m_lastMouseY;

        private static Byte[] m_keys = new Byte[325];

        public static Vector3 Look { get { return new Vector3(m_deltaMouseX, m_deltaMouseY, 0.0f); } }
        public static Vector2 Strafe
        {
            get
            {
                Vector2 strafeVec = new Vector2(0.0f, 0.0f);

                if ( m_keys['W'] != 0 ) strafeVec.X += 1.0f;
                if (m_keys['S'] != 0) strafeVec.X += -1.0f;

                if (m_keys['A'] != 0) strafeVec.Y += 1.0f;
                if (m_keys['D'] != 0) strafeVec.Y += -1.0f;

                return strafeVec;
            }
        }

        internal static void Update()
        {
            float x = 0.0f;
            float y = 0.0f;

            VCInteropInputGetMouse(ref x, ref y, ref Fire, ref AltFire);

            m_deltaMouseX = -x;
            m_deltaMouseY = -y;

            m_lastMouseX = x;
            m_lastMouseY = y;

            Marshal.Copy(VCInteropInputGetKeys(), m_keys, 0, 325);
        }

        public static bool IsKeyDown(int keyCode)
        {
            return m_keys[keyCode] == 1;
        }
    }
}
