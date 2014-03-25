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
        private static RenderViewport m_renderWindow;
        private static RenderedEntity m_renderEntity;

        public static void EditorMain()
        {
            PathUtilities.UpdatePathUtilities();

            EditorWindow EditorWindow = new EditorWindow(1680, 1050, "VC Engine Core - Thilenius - Alpha");

            PxPhysics.Initialize();
            VCEngineCore.Initialize();
            VCEngineCore.Start();

            LoopController.PassControlAndBegin();
        }


    }
}
