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

        private static float m_mouseX;
        private static float m_mouseY;

        private static bool m_mouseLeft;
        private static bool m_mouseright;

        private static Byte[] m_keys = new Byte[325];

        internal static void Update()
        {
            VCInteropInputGetMouse(ref m_mouseX, ref m_mouseY, ref m_mouseLeft, ref m_mouseright);

            Marshal.Copy(VCInteropInputGetKeys(), m_keys, 0, 325);
        }

        public static bool IsKeyDown(int keyCode)
        {
            return m_keys[keyCode] == 1;
        }
    }
}
