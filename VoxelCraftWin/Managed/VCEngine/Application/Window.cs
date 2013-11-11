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

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWindowGetSize(out int width, out int height);
        
		#endregion

        public static Point Size { get; private set; }
        public static Rectangle FullViewport { get { return new Rectangle(0, 0, Size); } }

        public static event EventHandler<ResizeEventArgs> Resize = delegate { };

        internal static void Initialize()
        {
            int w, h;
            VCInteropWindowGetSize(out w, out h);
            Size = new Point(w, h);
        }

        private static void GlfwSizeChangeHandler(int width, int height)
        {
            ResizeEventArgs args = new ResizeEventArgs { From = new Rectangle(0, 0, Size), To = new Rectangle(0, 0, width, height) };
            Size = new Point(width, height);
            Resize(null, args);
        }

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
