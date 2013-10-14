﻿using System;
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
                    VCEngineCore.PropagateUpdates();

                    Control.MainControl.Render();

                    // Rendering
                    GLRenderer.Render(GLRenderer.VC_BATCH_MIN, GLRenderer.VC_BATCH_MAX);

                    // Clear Input states & swap buffers
                    Input.ClearStates();
                    Window.SwapBuffers();
                }
            }

            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        }

    }
}
