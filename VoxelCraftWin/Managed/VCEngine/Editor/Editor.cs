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
        public static EditorGui EditorWindow;
        public static Boolean ThrotteledUpdate = true;
        public static TimeSpan LastCPUTime;
        private static int m_framesRemaining = 10;
        private static float m_drawTillTime;
        private static Stopwatch m_cpuTimeTimer = new Stopwatch();

        public static void EditorMain()
        {
            PathUtilities.UpdatePathUtilities();

            EditorWindow = new EditorGui(1280, 600, "VC Engine Core - Thilenius - Alpha");


            PxPhysics.Initialize();

            VCEngineCore.EditorMode = true;

            VCEngineCore.Initialize();
            EditorWorld.Initialize();

            VCEngineCore.Start();
            m_cpuTimeTimer.Start();

            while (!EditorWindow.ShouldClose() && EditorWindow.Input.GetKey(Input.Keys.Escape) != TriState.Pressed)
            {
                Window.PollEvents();

                if (ThrotteledUpdate)
                {
                    if (m_framesRemaining <= 0 && EditorWindow.GlfwInputState.KeysDown == 0 && Time.TotalTime > m_drawTillTime)
                    {
                        Time.Pause();
                        m_cpuTimeTimer.Stop();
                        Thread.Sleep(17);
                        continue;
                    }

                    Time.Resume();
                    m_cpuTimeTimer.Start();
                    m_framesRemaining--;
                }

                else
                {
                    // Clamp 80 FPS
                    Thread.Sleep(MathHelper.Clamp((int)((0.0125 - Time.DeltaTime) * 1000f), 0, 12));
                }

                Control.MainControl.PropagateUpdate();
                VCEngineCore.PropagateUpdates();

                Control.MainControl.Render();

                // Rendering
                EditorWindow.Activate();
                GLRenderer.Render(GLRenderer.VC_BATCH_MIN, GLRenderer.VC_BATCH_MAX);
                TestFixture.LatePerUpdate();

                // Step Input states & swap buffers
                EditorWindow.GlfwInputState.StepStates();
                LastCPUTime = m_cpuTimeTimer.Elapsed;
                m_cpuTimeTimer.Reset();

                EditorWindow.SwapBuffers();

                if (ThrotteledUpdate)
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

        #region Console Commands

        [ConsoleFunction("Boolean flag for redraw throttling", "Rendering")]
        public static String ThrottleRedraw(String[] args)
        {
            ThrotteledUpdate = Boolean.Parse(args[1]);

            return "";
        }

        #endregion

    }
}
