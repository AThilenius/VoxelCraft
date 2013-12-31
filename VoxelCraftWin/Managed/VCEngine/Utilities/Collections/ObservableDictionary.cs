using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ObservableDictionary<TKey, TValue> : Dictionary<TKey, TValue>
    {

        public event EventHandler OnCollectionChanged = delegate { };

        public new void Add( TKey key, TValue value )
        {
            base.Add(key, value);
            OnCollectionChanged(this, EventArgs.Empty);
        }

        public new TValue this[TKey i]
        {
            get { return base[i]; }
            set 
            {
                base[i] = value;
                OnCollectionChanged(this, EventArgs.Empty);
            }
        }

        public new bool Remove(TKey key)
        {
            bool result = base.Remove(key);
            OnCollectionChanged(this, EventArgs.Empty);

            return result;
        }

        public new void Clear()
        {
            base.Clear();
            OnCollectionChanged(this, EventArgs.Empty);
        }

    }
}
