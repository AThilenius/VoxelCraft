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

        public Vector3 Position;
        public Quaternion Rotation;
        public Vector3 Scale;
        
        public GameObject GameObject;

		internal Transform (GameObject parent)
		{
            GameObject = parent;
            GetData();
		}

        internal void SetData()
        {
            VCInteropTransformSetData(GameObject.UnManagedHandle,
                Position.X, Position.Y, Position.Z,
                Rotation.X, Rotation.Y, Rotation.Z, Rotation.W,
                Scale.X, Scale.Y, Scale.Z);
        }

        internal void GetData()
        {
            float px = 0.0f;
            float py = 0.0f;
            float pz = 0.0f;

            float rx = 1.0f;
            float ry = 1.0f;
            float rz = 1.0f;
            float rw = 0.0f;

            float sx = 1.0f;
            float sy = 1.0f;
            float sz = 1.0f;

            VCInteropTransformGetData(GameObject.UnManagedHandle,
                out px, out py, out pz,
                out rx, out ry, out rz, out rw,
                out sx, out sy, out sz);

            Position = new Vector3(px, py, pz);
            Rotation = new Quaternion(rx, ry, rz, rw);
            Scale = new Vector3(sx, sy, sz);
        }

	}
}

