using System;

namespace VCEngine
{
	internal static class ObjectStore
	{
		private static Object[] m_objects = new Object[1000];

		static ObjectStore()
		{
			Array.Clear (m_objects, 0, m_objects.Length);
		}

		internal static void RegisterObject ( Object obj, int handle )
		{
			// ReSize?
			while (handle >= m_objects.Length)
			{
				Object[] newObjectArray = new object[m_objects.Length * 2];
				Array.Clear (newObjectArray, 0, newObjectArray.Length);
				Array.Copy (m_objects, newObjectArray, m_objects.Length);
				m_objects = newObjectArray;
			}

			m_objects [handle] = obj;
		}

		internal static bool Contains (int handle)
		{
			return m_objects [handle] != null;
		}

		internal static Object GetObject (int handle)
		{
			return m_objects [handle];
		}

	}
}

