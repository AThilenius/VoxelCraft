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
                if (value == null)
                    Console.WriteLine("Null parent assignment from GO: " + UnManagedHandle);

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
            Transform.SetData();
            Start();

            for (int i = 0; i < Components.Count; i++)
                Components[i].Start();

            for (int i = 0; i < Children.Count; i++)
                Children[i].PropagateStart();

            Transform.SetData();
        }

        internal void PropagateUpdate()
        {
            Transform.GetData();
            Update();

            for (int i = 0; i < Components.Count; i++)
                Components[i].Update();

            for (int i = 0; i < Children.Count; i++)
                Children[i].PropagateUpdate();

            Transform.SetData();
        }

        internal void PropagateLateUpdate()
        {
            Transform.GetData();
            LateUpdate();

            for (int i = 0; i < Components.Count; i++)
                Components[i].LateUpdate();

            for (int i = 0; i < Children.Count; i++)
                Children[i].PropagateLateUpdate();

            Transform.SetData();
        }

        internal void PropagatePreRender()
        {
            Transform.GetData();
            PreRender();

            for (int i = 0; i < Components.Count; i++)
                Components[i].PreRender();

            for (int i = 0; i < Children.Count; i++)
                Children[i].PropagatePreRender();

            Transform.SetData();
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

