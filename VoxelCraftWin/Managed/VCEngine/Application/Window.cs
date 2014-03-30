using System;
using System.Collections.Generic;
using System.Diagnostics;
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
        extern static void VCInteropGLWindowSetTitle(int handle, String title);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowSetPos(int handle, int x, int y);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static void VCInteropGLWindowRegisterResizeCallback(GlfwFramebuferResizeDelegate callback);

        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropGLWindowRelease; } }
        
		#endregion

        public static List<Window> ActiveWindows = new List<Window>();
        public static Point MonitorSize
        {
            get
            {
                int w, h;
                VCInteropGetMonitorSize(out w, out h);
                return new Point(w, h);
            }
        }
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
        public DiagnosticsOverlay Diagnostics;

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

            // Add a Diagnostics Control
            Diagnostics = new DiagnosticsOverlay(this);
            MainControl.AddControl(Diagnostics);
            Diagnostics.Frame = MainControl.Frame;

            FrameBufferObject.Default.Bind();

            LoopController.OnLoop += HandleUpdate;
            ActiveWindows.Add(this);

            TrueSize = TrueSize * Gui.Scale;
        }

        new public void Dispose()
        {
            base.Dispose();

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

            // Pull Events
            VCInteropGLWindowPollEvents();

            // Check if a redraw has been requested
            //if (m_framesRemaining == 0 && Time.CurrentTime > m_drawTillTime)
            //    return;

            // Monitor LoopTime
            Stopwatch loopTimer = new Stopwatch();
            loopTimer.Start();

            // Update MainControl docking
            MainControl.Frame = MainControl.Frame;
            MainControl.PropagateUpdate();

            // Render this window
            VCInteropGLWindowActivate(UnManagedHandle);
            FrameBufferObject.Default.Clear(true, true);
            //SetViewport(new Rectangle(0, 0, TrueSize));
            MainControl.Render();



            // Force one last flush to render out anything still in the queue
            FlushRenderQueue();

            // Step Input states & swap buffers
            GlfwInputState.StepStates();

            // Monitor DrawTime
            Stopwatch drawTimer = new Stopwatch();
            drawTimer.Start();

            // Swap Buffers ( Also forces a flush )
            VCInteropGLWindowSwapBuffers(UnManagedHandle);

            // Update times
            loopTimer.Stop();
            drawTimer.Stop();
            LastLoopTime = loopTimer.Elapsed;
            LastDrawTime = drawTimer.Elapsed;

            m_framesRemaining = (m_framesRemaining <= 0) ? 0 : m_framesRemaining - 1;
        }

        public void ShouldRedraw(float time = -1.0f)
        {
            if (time == -1.0f)
                m_framesRemaining = 3;

            else
            {
                if ((Time.TotalTime + time + 0.5f) > m_drawTillTime)
                    m_drawTillTime = Time.TotalTime + time + 0.5f;
            }
        }

        public void FlushRenderQueue()
        {
            // Render out GUI
            Gui.Render();

            // Clear the DEPTH buffer
            FrameBufferObject.Default.Clear(false, true);
        }

        /// <summary>
        /// Sets the rendering viewport. Note: This will flush the rendering pipeline.
        /// </summary>
        /// <param name="viewport">The rendering canvas viewport</param>
        public void SetViewport(Rectangle viewport)
        {
            // Flush
            FlushRenderQueue();

            // Set the FBO viewport
            FrameBufferObject.Default.SetViewport(viewport);
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
