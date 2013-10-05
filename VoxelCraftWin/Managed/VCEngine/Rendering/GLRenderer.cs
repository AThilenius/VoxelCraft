using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace VCEngine
{
    public class GLRenderer
    {
        public const int VC_BATCH_SCENE = 20;
        public const int VC_BATCH_GUI_BASE = 25;
        public const int VC_BATCH_GUI = 30;

        public const int VC_BATCH_MIN = 1;
        public const int VC_BATCH_MAX = 1000000;

        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropRendererRender(int from, int to);

        #endregion

        public static void Render(int from, int to)
        {
            VCInteropRendererRender(from, to);
        }

    }
}
