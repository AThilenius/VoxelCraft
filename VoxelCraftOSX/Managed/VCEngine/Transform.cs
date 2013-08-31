using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class Transform : Component
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int VCInteropNewTransform();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void VCInteropReleaseTransform(int handle);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void VCInteropTransformSetPosition(int handle, float x, float y, float z);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void VCInteropTransformSetRotationEuler(int handle, float x, float y, float z);
		
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void VCInteropTransformSetRotationQuat(int handle, float x, float y, float z, float w);
		
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void VCInteropTransformSetScale(int handle, float x, float y, float z);

		#endregion

		//override internal int Handle { get; set; }

		public Transform ()
		{
			Handle = VCInteropNewTransform ();
		}

		internal Transform (int existingHandle)
		{
			Handle = existingHandle;
			ObjectStore.RegisterObject (this, Handle);
		}

		~Transform()
		{
			VCInteropReleaseTransform (Handle);
		}

		// HACK
		public void SetPosition (float x, float y, float z)
		{
			VCInteropTransformSetPosition (Handle, x, y, z);
		}

		// HACK
		public void SetRotationEler (float x, float y, float z)
		{
			VCInteropTransformSetRotationEuler (Handle, x, y, z);
		}


	}
}

