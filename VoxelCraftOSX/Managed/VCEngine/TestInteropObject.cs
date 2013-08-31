using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class TestInteropObject
	{
		#region Bindings
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int VCNewTestInteropObject();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void VCReleaseTestInteropObject(int handle);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void VCTestInteropObjectSetLocation(int handle, float x, float y, float z);
		#endregion

		private int m_unmanagedHandle = -1;

		public TestInteropObject ()
		{
			Console.WriteLine ("Managed: TestInteropObject CTor");

			m_unmanagedHandle = VCNewTestInteropObject ();

			if (m_unmanagedHandle == -1)
				Console.WriteLine ("Managed: Failed to get unmanaged handle for TestInteropObject");
		}

		~TestInteropObject()
		{
			Console.WriteLine ("Managed: TestInteropObject DTor");

			VCReleaseTestInteropObject (m_unmanagedHandle);
		}

		public void SetLocation(float x, float y, float z)
		{
			Console.WriteLine ("Managed: TestInteropObject SetLocation");

			VCTestInteropObjectSetLocation (m_unmanagedHandle, x, y, z);
		}

	}
}

