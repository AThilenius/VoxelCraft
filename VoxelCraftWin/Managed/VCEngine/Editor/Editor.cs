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
                VCEngineCore.Initialize();

                Control.MainControl = new Control();
                Control.MainControl.ScreenFrame = new Rectangle(0, 0, Window.Size);
                Control.MainControl.BorderColor = Color.Black;
                Control.MainControl.BackgroundColor = Color.Trasparent;
                Control.MainControl.HighlightBackgroundColor = Color.Trasparent;
                Control.MainControl.SetFirstResponder();

                MenuBar bar = new MenuBar();
                Control.MainControl.AddControl(bar);

                Menu testMenu1 = new Menu();
                Control.MainControl.AddControl(testMenu1);
                testMenu1.AddItemReverse("Close");
                testMenu1.AddItemReverse("Open");
                testMenu1.AddItemReverse("Save");

                Menu testMenu2 = new Menu();
                Control.MainControl.AddControl(testMenu2);
                testMenu2.AddItemReverse("Options");
                testMenu2.AddItemReverse("Find");
                testMenu2.AddItemReverse("Redo");
                testMenu2.AddItemReverse("Undo");

                bar.AddMenu("Close", testMenu1);
                bar.AddMenu("Options", testMenu2);


                // Load world here...

                VCEngineCore.Start();

                while (!Window.ShouldClose() && Input.GetKey(Input.Keys.Escape) != TriState.Pressed)
                {
                    // Mono
                    VCEngineCore.Update();
                    VCEngineCore.LateUpdate();
                    VCEngineCore.PreRender();
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
