using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class Window : MarshaledObject
    {
        #region Bindings

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GlfwFramebuferResizeDelegate(int handle, int x, int y);


        // Static
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowPollEvents();
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGetMonitorSize(out int width, out int height );

        
        // CTor DTor
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static int VCInteropGLWindowCreate(int width, int height, String title);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowRelease(int handle);

        
        // Instance
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGLWindowActivate(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowSwapBuffers(int handle);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static bool VCInteropGLWindowShouldClose(int handle);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowVSync(int handle, int enabled); 
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowGetSize(int handle, out int width, out int height);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowSetSize(int handle, int width, int height);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowGetPos(int handle, out int x, out int y);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowSetPos(int handle, int x, int y);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowRegisterResizeCallback(GlfwFramebuferResizeDelegate callback);

        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropGLWindowRelease; } }
        
		#endregion

        public Point Position
        {
            get
            {
                int x, y;
                VCInteropGLWindowGetPos(UnManagedHandle, out x, out y);
                return new Point(x, y);
            }

            set
            {
                VCInteropGLWindowSetPos(UnManagedHandle, value.X, value.Y);
            }
        }
        public Point ScaledSize 
        {
            get { return TrueSize / Gui.Scale; }
        }
        public Point TrueSize
        {
            get
            {
                int x, y;
                VCInteropGLWindowGetSize(UnManagedHandle, out x, out y);
                return new Point(x, y);
            }

            set
            {
                VCInteropGLWindowSetSize(UnManagedHandle,  value.X, value.Y);
            }
        }
        public Point MonitorSize
        {
            get
            {
                int w, h;
                VCInteropGetMonitorSize(out w, out h);
                return new Point(w, h);
            }
        }
        public Rectangle FullViewport { get { return new Rectangle(0, 0, ScaledSize); } }
        public event EventHandler<ResizeEventArgs> Resize = delegate { };

        public Window(int width, int height, String title)
        {
            UnManagedHandle = VCInteropGLWindowCreate(width, height, title);
            ObjectStore.RegisterObject(this, UnManagedHandle);

            // Possible problem here... This needs to be pinned so the GC doesn't move it
            VCInteropGLWindowRegisterResizeCallback((handle, newWidth, newHeight) =>
            {
                Window win = (Window)ObjectStore.GetObject(handle);
                win.GlfwSizeChangeHandler(newWidth, newHeight);
            });
        }

        public static void PollEvents()
        {
            VCInteropGLWindowPollEvents();
        }

        public void Activate()
        {
            VCInteropGLWindowActivate(UnManagedHandle);
        }

        public void SwapBuffers()
        {
            VCInteropGLWindowSwapBuffers(UnManagedHandle);
        }

        public bool ShouldClose()
        {
            return VCInteropGLWindowShouldClose(UnManagedHandle);
        }

        private void GlfwSizeChangeHandler(int width, int height)
        {
            Editor.ShouldRedraw();
            ResizeEventArgs args = new ResizeEventArgs { From = new Rectangle(Position, ScaledSize), To = (new Rectangle(Position, width, height) / Gui.Scale) };
            Resize(null, args);
        }

        #region Console Commands

        #endregion
    }
}
