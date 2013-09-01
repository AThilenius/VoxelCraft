using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class GameObject
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static int VCInteropNewGameObject();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropReleaseGameObject(int handle);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropGameObjectAttachComponent(int handle, int componentHandle);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropGameObjectSetParent(int handle, int parentHandle);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static int VCInteropGameObjectGetParent(int handle);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static int VCInteropGameObjectGetTransform(int handle);

		#endregion

		private GameObject m_parent;
		public GameObject Parent
		{
			get
			{
				if (m_parent == null)
				{
					// Get, or Create parent
					int parentHandle = VCInteropGameObjectGetParent (Handle);

					if (ObjectStore.Contains (parentHandle))
						m_parent = (GameObject)ObjectStore.GetObject (parentHandle);
					else
					{
						m_parent = new GameObject (parentHandle);
						ObjectStore.RegisterObject (m_parent, parentHandle);
					}
				}

				return m_parent;
			}
			set
			{
				VCInteropGameObjectSetParent (Handle, value.Handle);
				m_parent = value;
			}
		}

		private Transform m_trasform;
		public Transform Transform
		{
			get
			{
				if (m_trasform == null)
				{
					// Get, or Create parent
					int transformHandle = VCInteropGameObjectGetTransform (Handle);

					if (ObjectStore.Contains (transformHandle))
						m_trasform = (Transform)ObjectStore.GetObject (transformHandle);
					else
					{
						m_trasform = new Transform (transformHandle);
						ObjectStore.RegisterObject (m_trasform, transformHandle);
					}
				}

				return m_trasform;
			}
		}

		internal int Handle;

		public GameObject ()
		{
			Handle = VCInteropNewGameObject ();
			ObjectStore.RegisterObject (this, Handle);
		}

		internal GameObject(int existingHandle)
		{
			Handle = existingHandle;
		}

		~GameObject()
		{
			VCInteropReleaseGameObject (Handle);
		}

		public void AttachComponent (Component component)
		{
			Console.WriteLine ("= Attaching " + component.Handle + " to " + Handle);
			VCInteropGameObjectAttachComponent (Handle, component.Handle);

			component.GameObject = this;
			component.Transform = Transform;
		}

	}
}

