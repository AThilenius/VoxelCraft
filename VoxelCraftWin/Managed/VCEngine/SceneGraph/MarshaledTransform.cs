using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class MarshaledTransform : Transform
    {

        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGameObjectSetModelMatrix(int handle, Matrix4 matrix);

        #endregion

        public override Vector3 Position
        {
            get { return base.Position; }
            set
            {
                base.Position = value;
                m_wasUpdated = true;
            }
        }
        public override Quaternion Rotation
        {
            get { return base.Rotation; }
            set
            {
                base.Rotation = value;
                m_wasUpdated = true;
            }
        }
        public override Vector3 Scale
        {
            get { return base.Scale; }
            set
            {
                base.Scale = value;
                m_wasUpdated = true;
            }
        }

        private int m_parentHandle;
        private Boolean m_wasUpdated;

        public MarshaledTransform(int parentHandle)
        {
            m_parentHandle = parentHandle;
        }
        public override void PreRender()
        {
            if (m_wasUpdated)
            {
                // Set UnManaged transform matrix
                VCInteropGameObjectSetModelMatrix(m_parentHandle, TransformMatrix);
                m_wasUpdated = false;
            }

            base.PreRender();
        }

    }
}
