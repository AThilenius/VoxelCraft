using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ObservableHashSet<T> : HashSet<T>
    {
        public event EventHandler OnPreCollectionChanged = delegate { };
        public event EventHandler OnPostCollectionChanged = delegate { };

        public new bool Add(T item)
        {
            OnPreCollectionChanged(item, EventArgs.Empty);
            bool results = base.Add(item);
            OnPostCollectionChanged(item, EventArgs.Empty);

            return results;
        }

        public new void Clear()
        {
            OnPreCollectionChanged(null, EventArgs.Empty);
            base.Clear();
            OnPostCollectionChanged(null, EventArgs.Empty);
        }

        public new bool Remove(T item)
        {
            OnPreCollectionChanged(item, EventArgs.Empty);
            bool results = base.Remove(item);
            OnPostCollectionChanged(item, EventArgs.Empty);

            return results;
        }

        public new int RemoveWhere(Predicate<T> match)
        {
            OnPreCollectionChanged(null, EventArgs.Empty);
            int results = base.RemoveWhere(match);
            OnPostCollectionChanged(null, EventArgs.Empty);

            return results;
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
