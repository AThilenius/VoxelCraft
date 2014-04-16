using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace VCEngine
{
    public class Editor
    {

        public static void EditorMain()
        {
            PathUtilities.UpdatePathUtilities();

            //EditorWindow EditorWindow = new EditorWindow(1680, 1050, "VC Engine Core - Thilenius - Alpha");
            Window testWindow = new Window(800, 600, "Test Window");
            DevelopmentControl devCtrl = new DevelopmentControl(testWindow);
            testWindow.MainControl.AddControl(devCtrl);
            devCtrl.Dock = Control.Dockings.Fill;

            Shader.PreCacheAndMonitorShader(PathUtilities.ResourcesPath);
            LoopController.PassControlAndBegin();
        }

    }
}
