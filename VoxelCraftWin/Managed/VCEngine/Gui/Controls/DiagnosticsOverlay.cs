using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class DiagnosticsOverlay : Control
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropResourceManagerGetGPUMemoryUsage();

        #endregion

        public int DrawOverlayLevel = 0;
        public static int ManagedGLMemoryAlloced = 0;

        private int m_yOffset;
        private int m_frameCount;
        private Double m_lastLoopTime;
        private Double m_lastDrawTime;
        private PerformanceCounter m_ramAvalableCounter;

        private Font m_fontConsolas;

        public DiagnosticsOverlay(Window window) : base(window)
        {
            m_fontConsolas = Font.GetFont("Consolas", 24, ParentWindow);

            // Overlay ( Pass though, always on top )
            IsEventPassthrough = true;
            Layer = 10;

            ParentWindow.Resize += (s, a) => ScreenFrame = new Rectangle(0, 0, ParentWindow.FullViewport.Width, ParentWindow.FullViewport.Height);

            
        }

        protected override void Draw()
        {
            base.Draw();

            // Smooth out FPS values
            m_lastLoopTime = m_lastLoopTime * 0.9d + ParentWindow.LastLoopTime.TotalSeconds * 0.1d;
            m_lastDrawTime = m_lastDrawTime * 0.9d + ParentWindow.LastDrawTime.TotalSeconds * 0.1d;
            m_frameCount++;

            if ( DrawOverlayLevel == 0 )
                return;

            Rectangle sf = ScreenFrame;

            m_yOffset = 25;

            if (DrawOverlayLevel >= 2)
            {
                if (m_ramAvalableCounter == null)
                    m_ramAvalableCounter = new PerformanceCounter("Memory", "Available Bytes");

                DrawText("====  CPU Usage  ===============================================", sf);
                DrawText("Physical Memory Usage:        " + Process.GetCurrentProcess().WorkingSet64 / 1048576.0f + " MB", sf);
                DrawText("Physical Memory Available:    " + m_ramAvalableCounter.NextValue() / 1048576.0f + " MB", sf);
                DrawText("Base Priority:                " + Process.GetCurrentProcess().BasePriority, sf);
                DrawText("Priority Class:               " + Process.GetCurrentProcess().PriorityClass, sf);
                DrawText("User Processor Time:          " + Process.GetCurrentProcess().UserProcessorTime, sf);
                DrawText("Privileged Processor Time:    " + Process.GetCurrentProcess().PrivilegedProcessorTime, sf);
                DrawText("Total Processor Time:         " + Process.GetCurrentProcess().TotalProcessorTime, sf);
                DrawText("PagedSystemMemorySize64:      " + Process.GetCurrentProcess().PagedSystemMemorySize64 / 1048576.0f + " MB", sf);
                DrawText("PagedMemorySize64:            " + Process.GetCurrentProcess().PagedMemorySize64 / 1048576.0f + " MB", sf);
            }

            m_yOffset += 20;
            DrawText("====  GPU Usage  ===============================================", sf);
            DrawText("Full Loop FPS:                " + (1.0d / m_lastLoopTime).ToString("0000") + " FPS", sf);
            DrawText("OpenGL FPS:                   " + (1.0d / m_lastDrawTime).ToString("0000") + " FPS", sf);
            DrawText("Drawn Frames Count:           " + m_frameCount, sf);
            DrawText("GPU Memory Used:              " + ((float)(VCInteropResourceManagerGetGPUMemoryUsage() + ManagedGLMemoryAlloced) / (float)1000000.0f) + " MB", sf);

            m_yOffset += 20;
            DrawText("====  GUI  =====================================================", sf);
            DrawText("Resolution:                   " + ParentWindow.TrueSize, sf);
            DrawText("Gui Scaled Resolution:        " + ParentWindow.ScaledSize, sf);
            DrawText("Mouse:                        " + m_glfwInputState.MouseLocation, sf);
        }

        private void DrawText(string text, Rectangle sf)
        {
            m_fontConsolas.DrawStringBeveled(text, new Point(5, sf.Height - m_yOffset), new Color(255, 255, 0, 255));
            m_yOffset += 20;
        }

        #region Console Commands

        [ConsoleFunction("Sets the diagnostics drawing level. [0, 1, 2]", "Window")]
        public static String DrawDiagnostics(String[] args)
        {
            if (GeneralConsoleFunctions.SelectedWindow == null)
                return "Activate a window before calling window specific commands";

            GeneralConsoleFunctions.SelectedWindow.Diagnostics.DrawOverlayLevel = Int32.Parse(args[1]);
            return "";
        }

        #endregion

    }
}
