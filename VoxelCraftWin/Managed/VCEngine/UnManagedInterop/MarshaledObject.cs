using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public abstract class MarshaledObject
    {
        internal int UnManagedHandle = -1;

        protected delegate int UnManagedCTorDelegate ();
        protected delegate void UnManagedDTorDelegate (int handle);

        protected abstract UnManagedCTorDelegate UnManagedCTor { get; }
        protected abstract UnManagedDTorDelegate UnManagedDTor { get; }

        public MarshaledObject()
        {
            UnManagedHandle = UnManagedCTor();
            ObjectStore.RegisterObject(this, UnManagedHandle);
        }

        ~MarshaledObject()
        {
            if (UnManagedHandle == -1)
                return;

            UnManagedDTor(UnManagedHandle);
            ObjectStore.ReleaseHandle(UnManagedHandle);
            UnManagedHandle = -1;
        }

    }
}
