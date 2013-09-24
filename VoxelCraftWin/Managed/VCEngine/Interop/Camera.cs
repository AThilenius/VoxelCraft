using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class Camera : GameObject
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static int VCInteropNewCamera();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropReleaseCamera(int handle);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewCamera; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseCamera; } }

		#endregion

		public Camera ()
		{
			Console.WriteLine("= Camera created with handle: " + UnManagedHandle);
		}

        //public override void Update ()
        //{
        //    if (Input.IsKeyDown((int)'S'))
        //        Transform.Position = Transform.Position + new Vector3(0.0f, 0.0f, 5.0f) * Time.DeltaTime;
        //}

	}
}

