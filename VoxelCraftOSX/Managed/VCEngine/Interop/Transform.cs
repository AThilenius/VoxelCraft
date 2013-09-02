using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class Transform
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropTransformGetData(int handle,
            out float posX, out float posY, out float posZ,
            out float rotX, out float rotY, out float rotZ, out float rotW,
            out float sclX, out float sclY, out float sclZ);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropTransformSetData(int handle, 
            float posX, float posY, float posZ, 
            float rotX, float rotY, float rotZ, float rotW, 
            float sclX, float sclY, float sclZ);

		#endregion

		public Vector3 Position
		{
			get
			{
                GetData();
                return m_position;
			}

			set
			{
                m_position = value;
                SetData();
			}
		}
		public Quaternion Rotation
		{
			get
			{
                GetData();
                return m_rotation;
			}

			set
			{
                m_rotation = value;
                SetData();
			}
		}
		public Vector3 Scale
		{
			get
			{
                GetData();
                return m_scale;
			}

			set
			{
                m_scale = value;
                SetData();
			}
		}
        
        public GameObject GameObject;

        private Vector3 m_position;
        private Quaternion m_rotation;
        private Vector3 m_scale;

		internal Transform (GameObject parent)
		{
            GameObject = parent;
            GetData();
		}

        private void SetData()
        {
            VCInteropTransformSetData(GameObject.UnManagedHandle,
                m_position.X, m_position.Y, m_position.Z,
                m_rotation.X, m_rotation.Y, m_rotation.Z, m_rotation.W,
                m_scale.X, m_scale.Y, m_scale.Z);
        }

        private void GetData()
        {
            float px = 0.0f;
            float py = 0.0f;
            float pz = 0.0f;

            float rx = 0.0f;
            float ry = 0.0f;
            float rz = 0.0f;
            float rw = 0.0f;

            float sx = 1.0f;
            float sy = 1.0f;
            float sz = 1.0f;

            VCInteropTransformGetData(GameObject.UnManagedHandle,
                out px, out py, out pz,
                out rx, out ry, out rz, out rw,
                out sx, out sy, out sz);

            m_position = new Vector3(px, py, pz);
            m_rotation = new Quaternion(rx, ry, rz, rw);
            m_scale = new Vector3(sx, sy, sz);
        }

	}
}

