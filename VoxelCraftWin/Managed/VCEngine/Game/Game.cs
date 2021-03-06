﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Game
    {

        public static void GameMain()
        {
            VCEngineCore.Initialize();

            // Load world here...

            VCEngineCore.Start();

            while (!Window.ShouldClose() && Input.GetKey(Input.Keys.Escape) != TriState.Pressed)
            {
                // Mono
                VCEngineCore.Update();
                VCEngineCore.LateUpdate();
                VCEngineCore.PreRender();

                // Rendering
                GLRenderer.Render(GLRenderer.VC_BATCH_MIN, GLRenderer.VC_BATCH_MAX);

                // Windowing
                Window.SwapBuffers();
            }
        }

    }
}
