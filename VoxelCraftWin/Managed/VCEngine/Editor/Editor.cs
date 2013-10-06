﻿using System;
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

                MainControl = new Control();
                MainControl.ScreenFrame = new Rectangle(0, 0, Window.Size);
                MainControl.BorderColor = Color.Black;
                MainControl.BackgroundColor = Color.Trasparent;
                MainControl.HighlightBackgroundColor = Color.Trasparent;
                MainControl.SetFirstResponder();

                MenuBar bar = new MenuBar();
                MainControl.AddControl(bar);

                Menu testMenu1 = new Menu();
                MainControl.AddControl(testMenu1);
                testMenu1.AddItemReverse("Close");
                testMenu1.AddItemReverse("Open");
                testMenu1.AddItemReverse("Save");

                Menu testMenu2 = new Menu();
                MainControl.AddControl(testMenu2);
                testMenu2.AddItemReverse("Options");
                testMenu2.AddItemReverse("Find");
                testMenu2.AddItemReverse("Redo");
                testMenu2.AddItemReverse("Undo");

                bar.AddMenu("File", testMenu1);
                bar.AddMenu("Edit", testMenu2);


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