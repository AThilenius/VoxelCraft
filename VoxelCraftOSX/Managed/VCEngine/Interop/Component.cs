using System;

namespace VCEngine
{
	public abstract class Component
	{
		public GameObject GameObject;
		public Transform Transform;

		virtual internal int Handle { get; set; }

        public virtual void Start() { }
        public virtual void Update() { }
        public virtual void LateUpdate() { }
        public virtual void PreRender() { }
    }
}

