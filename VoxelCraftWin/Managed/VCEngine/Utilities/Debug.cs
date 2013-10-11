using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace VCEngine
{
    public static class Debug
    {
        #region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropDebugReset();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropDebugDrawLine(Vector3 from, Vector3 to, Color color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropDebugDrawCube(Vector3 corner, Vector3 scale, Color color);

        #endregion

        public static void DrawLine(Vector3 from, Vector3 to, Color color)
        {
            VCInteropDebugDrawLine(from, to, color);
        }

        public static void DrawCube(Vector3 corner, Vector3 scale, Color color)
        {
            VCInteropDebugDrawCube(corner, scale, color);
        }

        internal static void Reset()
        {
            VCInteropDebugReset();
        }

    }
}
