using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class GameObject : MarshaledObject
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static int VCInteropNewGameObject();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropReleaseGameObject(int handle);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropGameObjectSetParent(int handle, int parentHandle);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewGameObject; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseGameObject; } }

		#endregion

		private GameObject m_parent;
		public GameObject Parent
		{
			get
			{
				return m_parent;
			}
			set
			{
				VCInteropGameObjectSetParent (UnManagedHandle, value.UnManagedHandle);
				m_parent = value;
			}
		}

        public Transform Transform { get; private set; }

		public GameObject ()
		{
            this.Transform = new VCEngine.Transform(this);
		}

        public virtual void Start() { }
        public virtual void Update() { }
        public virtual void LateUpdate() { }
        public virtual void PreRender() { }

        internal void PropagateStart()
        {
            // For each in here...
            Start();
        }

        internal void PropagateUpdate()
        {
            Update();
        }

        internal void PropagateLateUpdate()
        {
            LateUpdate();
        }

        internal void PropagatePreRender()
        {
            PreRender();
        }

        // Need to finish later
        //public void AttachComponent (Component component)
        //{
        //    component.GameObject = this;
        //    component.Transform = Transform;
        //}
	}
}

