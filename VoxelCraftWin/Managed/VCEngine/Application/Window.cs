using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace VCEngine
{
    public class Window
    {
        #region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropWindowSwapBuffers();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static bool VCInteropWindowShouldClose();
        
		#endregion

        public static Point Size { get{ return new Point ( 1280, 800 ); } }

        public static void SwapBuffers()
        {
            VCInteropWindowSwapBuffers();
        }

        public static bool ShouldClose()
        {
            return VCInteropWindowShouldClose();
        }
    }
}
