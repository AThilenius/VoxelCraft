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
            DelayedInvokeHelper.Invoke(DelayInvokeOrder.PreSetup);

            EditorWindow EditorWindow = new EditorWindow(1680, 1050, "VC Engine Core - Thilenius - Alpha");

            DelayedInvokeHelper.Invoke(DelayInvokeOrder.PreDefault);
            DelayedInvokeHelper.Invoke(DelayInvokeOrder.Default);
            DelayedInvokeHelper.Invoke(DelayInvokeOrder.PostDefault);

            Shader.PreCacheAndMonitorShader(PathUtilities.ResourcesPath);
            LoopController.PassControlAndBegin();
        }

    }
}
