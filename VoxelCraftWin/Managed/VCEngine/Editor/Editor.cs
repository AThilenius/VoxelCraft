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

        public static void EditorMain()
        {
            PathUtilities.UpdatePathUtilities();

            EditorWindow EditorWindow = new EditorWindow(1280, 600, "VC Engine Core - Thilenius - Alpha");
            //EditorWindow SecondWindow = new EditorWindow(1280, 600, "VC Engine Core - Second Window");

            PxPhysics.Initialize();
            VCEngineCore.Initialize();
            VCEngineCore.Start();

            LoopController.PassControlAndBegin();
        }


    }
}
