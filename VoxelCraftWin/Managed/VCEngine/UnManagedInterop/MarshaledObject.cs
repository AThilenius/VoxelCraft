using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public abstract class MarshaledObject : IDisposable
    {
        internal int UnManagedHandle = -1;

        protected delegate int UnManagedCTorDelegate();
        protected delegate void UnManagedDTorDelegate(int handle);

        protected virtual UnManagedCTorDelegate UnManagedCTor { get { return null; } }
        protected virtual UnManagedDTorDelegate UnManagedDTor { get { return null; } }

        public MarshaledObject()
        {
            if (UnManagedCTor == null)
                return;

            UnManagedHandle = UnManagedCTor();
            ObjectStore.RegisterObject(this, UnManagedHandle);
        }

        public MarshaledObject(int existingHandle)
        {
            if (UnManagedDTor == null)
                return;

            if (UnManagedCTor != null)
            {
                UnManagedHandle = existingHandle;
                ObjectStore.RegisterObject(this, UnManagedHandle);
            }
        }

        ~MarshaledObject()
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
