using System;

namespace VCEngine
{
	public abstract class Component
	{
		public GameObject GameObject;
		public Transform Transform;

		protected Component()
		{
			ComponentRegistry.AllComponents.Add (this, this);
		}

		~Component()
		{
			ComponentRegistry.AllComponents.Remove (this);
		}

		virtual internal int Handle { get; set; }

		public virtual void Update()
		{

		}

		public virtual void LateUpdate()
		{

		}

	}
}

