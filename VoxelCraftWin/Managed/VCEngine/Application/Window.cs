using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class Window : MarshaledObject, IDisposable
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
        extern static void VCInteropGLWindowSetTitle(int handle, String title);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowSetPos(int handle, int x, int y);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowRegisterResizeCallback(GlfwFramebuferResizeDelegate callback);

        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropGLWindowRelease; } }
        
		#endregion

        public static List<Window> ActiveWindows = new List<Window>();
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
        public String Title
        {
            get { return m_title; }
            set
            {
                m_title = value;
                VCInteropGLWindowSetTitle(UnManagedHandle, value);
            }
        }
        public TimeSpan LastLoopTime;
        public TimeSpan LastDrawTime;
        public Rectangle FullViewport { get { return new Rectangle(0, 0, ScaledSize); } }
        public GlfwInputState GlfwInputState;
        public Input Input;
        public GuiDrawer Gui;
        public Control MainControl;
        public event EventHandler<ResizeEventArgs> Resize = delegate { };
        public event EventHandler OnDraw = delegate { };

        private String m_title;
        private int m_framesRemaining = 10;
        private float m_drawTillTime;


        public Window(int width, int height, String title)
        {
            UnManagedHandle = VCInteropGLWindowCreate(width, height, title);
            ObjectStore.RegisterObject(this, UnManagedHandle);
            m_title = title;

            // Possible problem here... This needs to be pinned so the GC doesn't move it
            VCInteropGLWindowRegisterResizeCallback((handle, newWidth, newHeight) =>
            {
                Window win = (Window)ObjectStore.GetObject(handle);
                win.GlfwSizeChangeHandler(newWidth, newHeight);
            });

            Input = new Input(this);
            GlfwInputState = Input.GlfwInputState;
            Gui = new GuiDrawer(this);

            MainControl = new Control(this);
            MainControl.ScreenFrame = new Rectangle(0, 0, FullViewport.Width, FullViewport.Height);
            MainControl.SetFirstResponder();

            FrameBufferObject.Default.Bind();

            LoopController.OnLoop += HandleUpdate;
            ActiveWindows.Add(this);
        }

        public void Dispose()
        {
            LoopController.OnLoop -= HandleUpdate;
            ActiveWindows.Remove(this);
        }

        private void HandleUpdate(Object sender, EventArgs args)
        {
            // Check if window should close
            if (VCInteropGLWindowShouldClose(UnManagedHandle))
            {
                Dispose();
                return;
            }

            // Check if a redraw has been requested
            if (m_framesRemaining == 0 && Time.CurrentTime > m_drawTillTime)
                return;

            // Monitor LoopTime
            Stopwatch loopTimer = new Stopwatch();
            loopTimer.Start();

            // Pull Events
            VCInteropGLWindowPollEvents();

            // Update MainControl docking
            MainControl.Frame = MainControl.Frame;
            MainControl.PropagateUpdate();

            // Render this window
            VCInteropGLWindowActivate(UnManagedHandle);
            MainControl.Render();

            // Needs to be made instance based!
            FrameBufferObject.Default.Clear(true, true);
            Gui.Render();

            // Allow for external drawing
            OnDraw(this, EventArgs.Empty);

            // Step Input states & swap buffers
            GlfwInputState.StepStates();

            // Monitor DrawTime
            Stopwatch drawTimer = new Stopwatch();
            drawTimer.Start();

            // Flush the GL pipe
            VCInteropGLWindowSwapBuffers(UnManagedHandle);

            // Update times
            loopTimer.Stop();
            drawTimer.Stop();
            LastLoopTime = loopTimer.Elapsed;
            LastDrawTime = drawTimer.Elapsed;

            m_framesRemaining = (m_framesRemaining <= 0) ? 0 : m_framesRemaining--;
        }

        public void ShouldRedraw()
        {
            m_framesRemaining = 3;
        }

        public void ShouldRedraw(float time)
        {
            // 0.5 Second buffer
            if ((Time.TotalTime + time + 0.5f) > m_drawTillTime)
                m_drawTillTime = Time.TotalTime + time + 0.5f;
        }

        private void GlfwSizeChangeHandler(int width, int height)
        {
            ShouldRedraw();
            ResizeEventArgs args = new ResizeEventArgs { From = new Rectangle(Position, ScaledSize), To = (new Rectangle(Position, width, height) / Gui.Scale) };
            Resize(null, args);
        }

        #region Console Commands

        #endregion
    }
}
