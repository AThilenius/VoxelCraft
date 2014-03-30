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
        public static Boolean ThrotteledUpdate = true;
        public static TimeSpan LastCPUTime;

        private static RenderWindow m_renderWindow;

        public static void EditorMain()
        {
            PathUtilities.UpdatePathUtilities();

            EditorWindow EditorWindow = new EditorWindow(1280, 600, "VC Engine Core - Thilenius - Alpha");
            //Window SecondWindow = new Window(1280, 600, "Second Window - Thilenius");

            // TEST CODE

            // Rendering
            m_renderWindow = new RenderWindow(EditorWindow);
            m_renderWindow.MainCamera.Fullscreen = true;

            RenderedEntity entity = new RenderedEntity();
            entity.Transform.Position = new Vector3(0, 0, -15);

            m_renderWindow.Entities.Add(entity);

            LoopController.OnLoop += (s, a) => m_renderWindow.RenderToScreen();

            // TEST CODE

            PxPhysics.Initialize();
            VCEngineCore.Initialize();
            VCEngineCore.Start();

            LoopController.PassControlAndBegin();
        }


    }
}
