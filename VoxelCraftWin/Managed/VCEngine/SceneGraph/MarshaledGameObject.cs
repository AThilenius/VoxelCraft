using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public abstract class MarshaledGameObject : GameObject, IDisposable
    {
        internal int UnManagedHandle = -1;

        protected virtual UnManagedCTorDelegate UnManagedCTor { get { return null; } }
        protected virtual UnManagedDTorDelegate UnManagedDTor { get { return null; } }

        public MarshaledGameObject()
        {
            if (UnManagedCTor == null)
                return;

            UnManagedHandle = UnManagedCTor();
            ObjectStore.RegisterObject(this, UnManagedHandle);

            // Overwrite Transform with a marshaled one
            Components.Remove(m_transform);
            m_transform = new MarshaledTransform(UnManagedHandle);
            Components.Add(m_transform);
        }

        public MarshaledGameObject(int existingHandle)
        {
            if (UnManagedDTor == null)
                return;

            if (UnManagedCTor != null)
            {
                UnManagedHandle = existingHandle;
                ObjectStore.RegisterObject(this, UnManagedHandle);
            }

            // Overwrite Transform with a marshaled one
            Components.Remove(m_transform);
            m_transform = new MarshaledTransform(UnManagedHandle);
            Components.Add(m_transform);
        }

        ~MarshaledGameObject()
        {
            if (UnManagedHandle == -1)
                return;

            if (UnManagedDTor != null)
            {
                UnManagedDTor(UnManagedHandle);
                ObjectStore.ReleaseHandle(UnManagedHandle);
                UnManagedHandle = -1;
            }
        }

        public void Dispose()
        {
            if (UnManagedHandle == -1)
                return;

            UnManagedDTor(UnManagedHandle);
            ObjectStore.ReleaseHandle(UnManagedHandle);
            UnManagedHandle = -1;
        }

    }
}
