using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class GLRenderer
    {
//#define VC_BATH_DEFAULT 2
//#define VC_BATCH_SCENE 2
//#define VC_BATCH_GUI_BASE 3
//#define VC_BATCH_GUI 5
//#define VC_BATCH_MIN 1
//#define VC_BATCH_MAX 16
        public const int VC_BATCH_SCENE = 2;
        public const int VC_BATCH_GUI_BASE = 3;
        public const int VC_BATCH_GUI = 5;

        public const int VC_BATCH_MIN = 1;
        public const int VC_BATCH_MAX = 16;

        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropRendererRender(int from, int to);

        #endregion

        public static void Render(int from, int to)
        {
            VCInteropRendererRender(from, to);
        }

    }
}
