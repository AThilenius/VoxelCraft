using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class Window
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropWindowSwapBuffers();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropWindowPollEvents();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static bool VCInteropWindowShouldClose();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropWindowVSync(int enabled); 

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropWindowGetSize(out int width, out int height);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropWindowSetSize(int width, int height);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropWindowGetPos(out int x, out int y);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropWindowSetPos(int x, int y);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGetMonitorSize(out int width, out int height);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwFramebuferResizeDelegate(int x, int y);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropRegisterResizeCallback(GlfwFramebuferResizeDelegate callback);
        
		#endregion

        public static Point Position
        {
            get
            {
                int x, y;
                VCInteropWindowGetPos(out x, out y);
                return new Point(x, y);
            }

            set
            {
                VCInteropWindowSetPos(value.X, value.Y);
            }
        }
        public static Point ScaledSize 
        {
            get { return TrueSize / Gui.Scale; }
        }
        public static Point TrueSize
        {
            get
            {
                int x, y;
                VCInteropWindowGetSize(out x, out y);
                return new Point(x, y);
            }

            set
            {
                VCInteropWindowSetSize(value.X, value.Y);
            }
        }
        public static Point MonitorSize
        {
            get
            {
                int w, h;
                VCInteropGetMonitorSize(out w, out h);
                return new Point(w, h);
            }
        }
        public static Rectangle FullViewport { get { return new Rectangle(0, 0, ScaledSize); } }

        public static event EventHandler<ResizeEventArgs> Resize = delegate { };

        internal static void Initialize()
        {
            VCInteropRegisterResizeCallback((width, height) => GlfwSizeChangeHandler(width, height));
        }

        private static void GlfwSizeChangeHandler(int width, int height)
        {
            Editor.ShouldRedraw();
            ResizeEventArgs args = new ResizeEventArgs { From = new Rectangle(Position, ScaledSize), To = (new Rectangle(Position, width, height) / Gui.Scale) };
            //TrueSize = new Point(width, height);
            Resize(null, args);
        }

        public static void SwapBuffers()
        {
            VCInteropWindowSwapBuffers();
        }

        public static void PollEvents()
        {
            VCInteropWindowPollEvents();
        }

        public static bool ShouldClose()
        {
            return VCInteropWindowShouldClose();
        }

        #region Console Commands

        [ConsoleFunction("Boolean flag for V-Sync", "Rendering")]
        public static String VSync(String[] args)
        {
            VCInteropWindowVSync(Boolean.Parse(args[1]) ? 1 : 0);

            return "";
        }

        #endregion
    }
}
