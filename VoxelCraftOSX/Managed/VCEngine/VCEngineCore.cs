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
            SceneGraph.RootNode = new GameObject();
		}

        public virtual void Start()
        {
            SceneGraph.RootNode.PropagateStart();
        }

		public virtual void Update() 
		{
            Time.Update();
            Input.Update();
            SceneGraph.RootNode.PropagateUpdate();
		}

		public virtual void LateUpdate() 
		{
            SceneGraph.RootNode.PropagateLateUpdate();
		}

        public virtual void PreRender()
        {
            SceneGraph.RootNode.PropagatePreRender();
        }
	}
}

