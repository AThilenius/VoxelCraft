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

        public static float m_mouseX;
        public static float m_mouseY;

        private static bool Fire;
        private static bool AltFire;

        private static Byte[] m_keys = new Byte[325];

        public static Vector2 Look { get { return new Vector2(m_mouseX, m_mouseY); } }
        public static Vector2 Strafe
        {
            get
            {
                Vector2 strafeVec = new Vector2();
                strafeVec.X += m_keys['W'] == 1 ? 1.0f : 0.0f;
                strafeVec.X -= m_keys['S'] == 1 ? 1.0f : 0.0f;
                strafeVec.Y += m_keys['D'] == 1 ? 1.0f : 0.0f;
                strafeVec.Y -= m_keys['A'] == 1 ? 1.0f : 0.0f;
                return strafeVec;
            }
        }

        internal static void Update()
        {
            VCInteropInputGetMouse(ref m_mouseX, ref m_mouseY, ref Fire, ref AltFire);

            Marshal.Copy(VCInteropInputGetKeys(), m_keys, 0, 325);
        }

        public static bool IsKeyDown(int keyCode)
        {
            return m_keys[keyCode] == 1;
        }
    }
}
