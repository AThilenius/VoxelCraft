using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class FrameBufferObject : MarshaledObject
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropVCGLFrameBufferGetDefault();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropVCGLFrameBufferBind(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropVCGLFrameBufferSetClearColor(int handle, Vector4 color);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropVCGLFrameBUfferClear(int handle, bool color, bool depth);

        #endregion

        public static FrameBufferObject Default
        {
            get
            {
                if (m_defaultFBO == null)
                {
                    m_defaultFBO = new FrameBufferObject();
                    m_defaultFBO.UnManagedHandle = VCInteropVCGLFrameBufferGetDefault();
                }

                return m_defaultFBO;
            }
        }
        private static FrameBufferObject m_defaultFBO = null;

        public Color ClearColor
        {
            set
            {
                VCInteropVCGLFrameBufferSetClearColor(UnManagedHandle, new Vector4(value.R, value.G, value.B, value.A));
            }
        }

        private FrameBufferObject()
        {
        }

        public void Bind()
        {
            VCInteropVCGLFrameBufferBind(UnManagedHandle);
        }

        public void Clear(Boolean color, Boolean depth)
        {
            if (!color && !depth)
            {
                Log.Error("Must clear Color or Depth or Both", "Rendering");
                return;
            }

            VCInteropVCGLFrameBUfferClear(UnManagedHandle, color, depth);
        }

    }
}
