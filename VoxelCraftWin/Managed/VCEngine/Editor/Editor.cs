using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace VCEngine
{
    public class Editor
    {

        public static void EditorMain()
        {
            try
            {
                VCEngineCore.EditorMode = true;

                VCEngineCore.Initialize();
                EditorGui.Initialize();
                EditorWorld.Initialize();

                VCEngineCore.Start();

                while (!Window.ShouldClose() && Input.GetKey(Input.Keys.Escape) != TriState.Pressed)
                {
                    Control.MainControl.PropagateUpdate();
                    VCEngineCore.PropagateUpdates();

                    Control.MainControl.Render();

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

    }
}
