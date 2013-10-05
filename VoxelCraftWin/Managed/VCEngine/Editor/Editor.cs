using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace VCEngine
{
    public class Editor
    {
        public static Control MainControl;

        public static void EditorMain()
        {
            try
            {
                VCEngineCore.Initialize();
                MainControl = new Control(new Rectangle(0, 0, Window.Size), "Main", null);
                MainControl.BorderColor = Color.Black;
                MainControl.BackgroundColor = Color.Trasparent;
                MainControl.HighlightBackgroundColor = Color.Trasparent;
                MainControl.SetFirstResponder();

                Control second = new Control(new Rectangle(200, 200, 400, 400), "Second", MainControl);
                second.HighlightBackgroundColor = Color.ControlRed;
                MainControl.Children.Add(second);

                Control third = new Control(new Rectangle(200, 200, 150, 25), "Third", second);
                third.HighlightBackgroundColor = Color.ControlGreen;
                second.Children.Add(third);

                // Load world here...

                VCEngineCore.Start();

                while (!Window.ShouldClose() && !Input.IsKeyDown(Input.Keys.Escape))
                {
                    // Mono
                    VCEngineCore.Update();
                    VCEngineCore.LateUpdate();
                    VCEngineCore.PreRender();
                    MainControl.Render();

                    // Rendering
                    GLRenderer.Render(GLRenderer.VC_BATCH_MIN, GLRenderer.VC_BATCH_MAX);

                    // Windowing
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
