using System;
using System.Runtime.InteropServices;

namespace VCEngine
{
	public class Transform
	{
		#region Bindings

		[DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static Vector3 VCInteropTransformGetPosition(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static Quaternion VCInteropTransformGetRotation(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static Vector3 VCInteropTransformGetScale(int handle);


        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropTransformSetPosition(int handle, Vector3 pos);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropTransformSetRotation(int handle, Quaternion rot);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropTransformSetScale(int handle, Vector3 scale);

		#endregion

        public Vector3 Position
        {
            get 
            { 
                if (InvertPosition)
                    return -VCInteropTransformGetPosition(GameObject.UnManagedHandle); 
                else
                    return VCInteropTransformGetPosition(GameObject.UnManagedHandle);
            }
            set 
            {
                if (InvertPosition)
                    VCInteropTransformSetPosition(GameObject.UnManagedHandle, -value); 
                else
                    VCInteropTransformSetPosition(GameObject.UnManagedHandle, value); 
            }
        }
        public Quaternion Rotation
        {
            get { return VCInteropTransformGetRotation(GameObject.UnManagedHandle); }
            set { VCInteropTransformSetRotation(GameObject.UnManagedHandle, value); }
        }
        public Vector3 Scale
        {
            get { return VCInteropTransformGetScale(GameObject.UnManagedHandle); }
            set { VCInteropTransformSetScale(GameObject.UnManagedHandle, value); }
        }
        
        public GameObject GameObject;

        internal bool InvertPosition;

		internal Transform (GameObject parent)
		{
            GameObject = parent;
		}

	}
}

