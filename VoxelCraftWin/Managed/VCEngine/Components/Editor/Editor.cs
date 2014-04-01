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

            EditorWindow EditorWindow = new EditorWindow(1680, 1050, "VC Engine Core - Thilenius - Alpha");

            //Window testWindow = new Window(683, 683, "Test Window");
            //MaterialPreviewer matPrev = new MaterialPreviewer(testWindow);
            //testWindow.MainControl.AddControl(matPrev);
            //matPrev.Dock = Control.Dockings.Fill;
            //matPrev.OpenMaterialPath(@"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\VoxelCraftWin\Assets\Materials\Filters\AvgFilter.vcmaterial");
            
            Shader.PreCacheAndMonitorShader(PathUtilities.ResourcesPath);
            LoopController.PassControlAndBegin();
        }

    }
}
