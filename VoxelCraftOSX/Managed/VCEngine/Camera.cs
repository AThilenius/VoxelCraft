using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class Camera : Component
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int VCInteropNewCamera();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void VCInteropReleaseCamera(int handle);

		#endregion


		//new internal int Handle;

		public Camera ()
		{
			Handle = VCInteropNewCamera ();
			ObjectStore.RegisterObject (this, Handle);

			Console.WriteLine("Managed: Camera create with handle: " + Handle);
		}

		internal Camera (int existingHandle)
		{
			Handle = existingHandle;
		}

		~Camera()
		{
			VCInteropReleaseCamera (Handle);
		}

	}
}

