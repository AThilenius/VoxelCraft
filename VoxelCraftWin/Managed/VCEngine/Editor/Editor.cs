using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace VCEngine
{
    public class Editor
    {
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropInitalizeApplication();

        public static TimeSpan LastCPUTime;
        private static int m_framesRemaining = 10;
        private static float m_drawTillTime;
        private static Stopwatch m_cpuTimeTimer = new Stopwatch();

        public static void EditorMain()
        {
            VCInteropInitalizeApplication();

            VCEngineCore.EditorMode = true;

            GlfwInputState.Initialize();
            VCEngineCore.Initialize();
            EditorGui.Initialize();
            EditorWorld.Initialize();

            VCEngineCore.Start();
            m_cpuTimeTimer.Start();

            while (!Window.ShouldClose() && Input.GetKey(Input.Keys.Escape) != TriState.Pressed)
            {
                Window.PollEvents();

                if (m_framesRemaining <= 0 && GlfwInputState.KeysDown == 0 && Time.TotalTime > m_drawTillTime)
                {
                    Time.Pause();
                    m_cpuTimeTimer.Stop();
                    Thread.Sleep(17);
                    continue;
                }

                Time.Resume();
                m_cpuTimeTimer.Start();
                m_framesRemaining--;

                Control.MainControl.PropagateUpdate();
                VCEngineCore.PropagateUpdates();

                Control.MainControl.Render();
                TestFixture.LatePerUpdate();

                // Rendering
                GLRenderer.Render(GLRenderer.VC_BATCH_MIN, GLRenderer.VC_BATCH_MAX);

                // Step Input states & swap buffers
                GlfwInputState.StepStates();
                LastCPUTime = m_cpuTimeTimer.Elapsed;
                m_cpuTimeTimer.Reset();

                Window.SwapBuffers();

                m_cpuTimeTimer.Start();
            }
        }

        public static void ShouldRedraw()
        {
            m_framesRemaining = 3;
        }

        public static void ShouldRedraw(float time)
        {
            // 0.5 Second buffer
            if ( (Time.TotalTime + time + 0.5f) > m_drawTillTime)
                m_drawTillTime = Time.TotalTime + time + 0.5f;
        }

    }
}
