using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace VCEngine
{
	public class GameObject
	{
        public GameObject Parent
        {
            get { return m_parent; }
            set 
            {
                if (m_parent == value)
                    return;

                if (m_parent != null && m_parent.Children.Contains(this))
                    m_parent.Children.Remove(this);

                m_parent = value;

                if (value != null && !m_parent.Children.Contains(this))
                    m_parent.Children.Add(this);
            }
        }
        public ObservableList<GameObject> Children { get { return m_children; } }
        public Transform Transform { get { return m_transform; } }

        public ObservableList<Component> Components = new ObservableList<Component>();

        protected GameObject m_parent;
        protected Transform m_transform;
        protected ObservableList<GameObject> m_children = new ObservableList<GameObject>();

		public GameObject ()
		{
            Parent = SceneGraph.RootNode;
            m_transform = new Transform();
            Components.OnCollectionChanged += (s, a) =>
                {
                    if (a.WasRemoved)
                    {
                        a.Item.GameObject = null;
                        a.Item.Transform = null;
                    }

                    else
                    {
                        a.Item.GameObject = this;
                        a.Item.Transform = Transform;
                    }
                };
            Children.OnCollectionChanged += (s, a) =>
                {
                    if (a.WasRemoved)
                        a.Item.Parent = null;

                    else
                        a.Item.Parent = this;
                };

            Components.Add(m_transform);
		}

        public virtual void Start() 
        {
            for (int i = 0; i < Components.Count; i++)
                Components[i].Start();

            for (int i = 0; i < Children.Count; i++)
                Children[i].Start();
        }

        public virtual void Update() 
        {
            for (int i = 0; i < Components.Count; i++)
                Components[i].Update();

            for (int i = 0; i < Children.Count; i++)
                Children[i].Update();
        }

        public virtual void LateUpdate()
        {
            for (int i = 0; i < Components.Count; i++)
                Components[i].LateUpdate();

            for (int i = 0; i < Children.Count; i++)
                Children[i].Update();
        }

        public virtual void PreRender()
        {
            for (int i = 0; i < Components.Count; i++)
                Components[i].PreRender();

            for (int i = 0; i < Children.Count; i++)
                Children[i].PreRender();
        }

    }
}

