using System;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using System.Threading;

namespace VCEngine
{
	public class VCEngineCore
	{
		public virtual void Initalize()
		{
			Console.WriteLine ("= VCEngineCore::Intalize");
		}

		public virtual void Update() 
		{
            Time.Update();
            Input.Update();

			foreach (Component cmpt in ComponentRegistry.AllComponents.Keys)
				cmpt.Update ();
		}

		public virtual void LateUpdate() 
		{
			foreach (Component cmpt in ComponentRegistry.AllComponents.Keys)
				cmpt.LateUpdate ();
		}
	}
}

