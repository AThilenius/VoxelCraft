using System;
using System.Collections;
using System.Collections.Generic;

namespace VCEngine
{
	public static class ComponentRegistry
	{
		// No HashSet... wtf mono...
		public static Dictionary<Component, Component> AllComponents = new Dictionary<Component, Component>();
	}
}