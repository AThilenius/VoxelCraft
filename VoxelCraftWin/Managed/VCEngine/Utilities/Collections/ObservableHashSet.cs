using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ObservableHashSet<T> : HashSet<T>
    {
        public class AddRemoveEventArgs : EventArgs
        {
            public Boolean WasRemoved;
            public T Item;
        }

        public event EventHandler<AddRemoveEventArgs> OnCollectionChanged = delegate { };
        public event EventHandler OnClear = delegate {};

        public new bool Add(T item)
        {
            bool results = base.Add(item);
            OnCollectionChanged(this, new AddRemoveEventArgs { WasRemoved = false, Item = item });

            return results;
        }

        public new void Clear()
        {
            base.Clear();
            OnClear(this, EventArgs.Empty);
        }

        public new bool Remove(T item)
        {
            bool results = base.Remove(item);
            OnCollectionChanged(this, new AddRemoveEventArgs { WasRemoved = true, Item = item });

            return results;
        }

        public new int RemoveWhere(Predicate<T> match)
        {
            throw new NotSupportedException("Cannot use mass changing with an observable collection");
        }

    }

    public static class ExtensionObserHashSet
    {
        public static ObservableHashSet<T> ToObservable<T>(this HashSet<T> instance)
        {
            ObservableHashSet<T> oHash = new ObservableHashSet<T>();

            foreach (T item in instance)
                oHash.Add(item);

            return oHash;
        }
    }

}
