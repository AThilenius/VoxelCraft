using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class SceneGraph
	{
		#region Bindings
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static int VCInteropGetStaticHandle();
		#endregion

		private SceneGraph () { }

	}
}

