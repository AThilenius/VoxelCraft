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

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static Vector3 VCInteropCameraScreenPointToRay(int handle, int x, int y);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewCamera; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseCamera; } }

		#endregion

		public Camera ()
		{
            Transform.InvertPosition = true;

			Console.WriteLine("= Camera created with handle: " + UnManagedHandle);
		}

        public Ray ScreenPointToRay(int x, int y)
        {
            return new Ray
            {
                Direction = -Transform.Rotation.Forward,
                Origin = Transform.Position,
                MaxDistance = float.PositiveInfinity
            };
        }

	}
}

