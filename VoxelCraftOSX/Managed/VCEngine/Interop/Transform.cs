using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class Transform : Component
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static int VCInteropNewTransform();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropReleaseTransform(int handle);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropTransformSetPosition(int handle, float x, float y, float z);
		
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropTransformSetRotationQuat(int handle, float x, float y, float z, float w);
		
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropTransformSetScale(int handle, float x, float y, float z);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropTransformGetPosition (int handle, ref float x, ref float y, ref float z);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropTransformGetRotation(int handle, ref float x, ref float y, ref float z, ref float w);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropTransformGetScale(int handle, ref float x, ref float y, ref float z);

		#endregion

		public Vector3 Position
		{
			get
			{
				float x = 0.0f;
				float y = 0.0f;
				float z = 0.0f;
				VCInteropTransformGetPosition (Handle, ref x, ref y, ref z);
				return new Vector3 (x, y, z);
			}

			set
			{
				VCInteropTransformSetPosition (Handle, value.X, value.Y, value.Z);
			}
		}

		public Quaternion Rotation
		{
			get
			{
				float x = 0.0f;
				float y = 0.0f;
				float z = 0.0f;
				float w = 0.0f;
				VCInteropTransformGetRotation (Handle, ref x, ref y, ref z, ref w);
				return new Quaternion (x, y, z, w);
			}

			set
			{
				VCInteropTransformSetRotationQuat (Handle, value.X, value.Y, value.Z, value.W);
			}
		}

		public Vector3 Scale
		{
			get
			{
				float x = 0.0f;
				float y = 0.0f;
				float z = 0.0f;
				VCInteropTransformGetScale (Handle, ref x, ref y, ref z);
				return new Vector3 (x, y, z);
			}

			set
			{
				VCInteropTransformSetScale (Handle, value.X, value.Y, value.Z);
			}
		}

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


	}
}

