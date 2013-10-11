using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class Transform
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static Vector3 VCInteropTransformGetPosition(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static Quaternion VCInteropTransformGetRotation(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static Vector3 VCInteropTransformGetScale(int handle);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropTransformSetPosition(int handle, Vector3 pos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropTransformSetRotation(int handle, Quaternion rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
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

