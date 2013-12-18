using System;
using System.Collections.Generic;
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

        private static int m_framesRemaining = 10;

        public static void EditorMain()
        {
            try
            {
                VCInteropInitalizeApplication();

                VCEngineCore.EditorMode = true;

                GlfwInputState.Initialize();
                VCEngineCore.Initialize();
                EditorGui.Initialize();
                EditorWorld.Initialize();

                VCEngineCore.Start();

                while (!Window.ShouldClose() && Input.GetKey(Input.Keys.Escape) != TriState.Pressed)
                {
                    Window.PollEvents();

                    if (m_framesRemaining == 0 && GlfwInputState.KeysDown == 0)
                    {
                        Time.Pause();
                        Thread.Sleep(17);
                        continue;
                    }

                    Time.Resume();
                    m_framesRemaining--;

                    Control.MainControl.PropagateUpdate();
                    VCEngineCore.PropagateUpdates();

                    Control.MainControl.Render();
                    TestFixture.LatePerUpdate();

                    // Rendering
                    GLRenderer.Render(GLRenderer.VC_BATCH_MIN, GLRenderer.VC_BATCH_MAX);

                    // Step Input states & swap buffers
                    GlfwInputState.StepStates();
                    Window.SwapBuffers();
                }
            }

            catch (Exception ex)
            {
                Console.WriteLine("Managed Exception: " + ex.Message);
                Console.ReadLine();
            }
        }

        public static void ShouldRedraw()
        {
            m_framesRemaining = 3;
        }

    }
}
