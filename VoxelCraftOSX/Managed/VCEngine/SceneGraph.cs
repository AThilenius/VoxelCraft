using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class SceneGraph
	{
		#region Bindings
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int VCInteropGetStaticHandle();
		#endregion

		private SceneGraph () { }

	}
}

