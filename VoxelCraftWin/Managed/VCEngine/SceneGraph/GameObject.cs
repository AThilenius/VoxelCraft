using System;
using System.Collections.Generic;
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
                if (m_parent != null)
                    m_parent.Children.Remove(this);

				m_parent = value;

                if (value != null)
                {
                    VCInteropGameObjectSetParent(UnManagedHandle, value.UnManagedHandle);
                    value.Children.Add(this);
                }
			}
		}
        public List<GameObject> Children = new List<GameObject>();
        public List<Component> Components = new List<Component>();
        public Transform Transform { get; private set; }

		public GameObject ()
		{
            this.Transform = new VCEngine.Transform(this);
            Parent = SceneGraph.RootNode;
		}

        ~GameObject()
        {
            Parent = null;
        }

        public virtual void Start() { }
        public virtual void Update() { }
        public virtual void LateUpdate() { }
        public virtual void PreRender() { }

        internal void PropagateStart()
        {
            Start();

            for (int i = 0; i < Components.Count; i++)
                Components[i].Start();

            for (int i = 0; i < Children.Count; i++)
                Children[i].PropagateStart();
        }

        internal void PropagateUpdate()
        {
            Update();

            for (int i = 0; i < Components.Count; i++)
                Components[i].Update();

            for (int i = 0; i < Children.Count; i++)
                Children[i].PropagateUpdate();
        }

        internal void PropagateLateUpdate()
        {
            LateUpdate();

            for (int i = 0; i < Components.Count; i++)
                Components[i].LateUpdate();

            for (int i = 0; i < Children.Count; i++)
                Children[i].PropagateLateUpdate();
        }

        internal void PropagatePreRender()
        {
            PreRender();

            for (int i = 0; i < Components.Count; i++)
                Components[i].PreRender();

            for (int i = 0; i < Children.Count; i++)
                Children[i].PropagatePreRender();
        }

        // Need to finish later
        public void AttachComponent(Component component)
        {
            component.GameObject = this;
            component.Transform = Transform;
            Components.Add(component);
        }

        public void RemoveComponent(Component component)
        {
            Components.Remove(component);
            component.GameObject = null;
            component.Transform = null;
        }
	}
}

