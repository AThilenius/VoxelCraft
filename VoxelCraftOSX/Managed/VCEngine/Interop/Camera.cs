using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class Camera : Component
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static int VCInteropNewCamera();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropReleaseCamera(int handle);

		#endregion

		public Camera ()
		{
			Handle = VCInteropNewCamera ();
			ObjectStore.RegisterObject (this, Handle);

			Console.WriteLine("= Camera create with handle: " + Handle);
		}

		internal Camera (int existingHandle)
		{
			Handle = existingHandle;
		}

		~Camera()
		{
			VCInteropReleaseCamera (Handle);
		}

		public override void Update ()
		{
            if (Input.IsKeyDown((int)'S'))
                Transform.Position = Transform.Position + new Vector3(0.0f, 0.0f, 5.0f) * Time.DeltaTime;
		}

	}
}

