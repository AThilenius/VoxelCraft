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
        private static RenderWindow m_renderWindow;
        private static RenderedEntity m_renderEntity;

        public static void EditorMain()
        {
            PathUtilities.UpdatePathUtilities();

            EditorWindow EditorWindow = new EditorWindow(1920, 900, "VC Engine Core - Thilenius - Alpha");
            //Window SecondWindow = new Window(1024, 1024, "Second Window - Thilenius");

            PxPhysics.Initialize();
            VCEngineCore.Initialize();
            VCEngineCore.Start();


            // TEST CODE
            //m_renderWindow = new RenderWindow(SecondWindow);
            //m_renderWindow.MainCamera.Fullscreen = true;
            ////m_renderWindow.MainCamera.Viewport = new Rectangle(0, 0, 1024, 1024);

            //m_renderEntity = new RenderedEntity(@"Models\Plane.obj", @"Materials\HLineFilter.vcmaterial");
            //m_renderEntity.Transform.Position = new Vector3(-0.5f, -0.5f, -0.75f);

            //m_renderWindow.Entities.Add(m_renderEntity);
            // TEST CODE

            LoopController.PassControlAndBegin();
        }


    }
}
