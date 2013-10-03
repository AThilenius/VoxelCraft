using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Simi.Core.iOS.Utilities.Collections
{
    public class ObservableDictionary<TKey, TValue> : Dictionary<TKey, TValue>, IObservableCollection
    {

        public event EventHandler OnPreCollectionChanged = delegate { };
        public event EventHandler OnPostCollectionChanged = delegate { };

        public new void Add( TKey key, TValue value )
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.Add(key, value);
            OnPostCollectionChanged(this, EventArgs.Empty);
        }

        public new TValue this[TKey i]
        {
            get { return base[i]; }
            set 
            {
                OnPreCollectionChanged(this, EventArgs.Empty);
                base[i] = value;
                OnPostCollectionChanged(this, EventArgs.Empty);
            }
        }

        public new bool Remove(TKey key)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            bool result = base.Remove(key);
            OnPostCollectionChanged(this, EventArgs.Empty);

            return result;
        }

        public new void Clear()
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.Clear();
            OnPostCollectionChanged(this, EventArgs.Empty);
        }

    }
}
