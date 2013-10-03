using ProtoBuf;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Simi.Core.iOS.Utilities.Collections
{
    public class ObservableHashSet<T> : HashSet<T>, IObservableCollection
    {
        public event EventHandler OnPreCollectionChanged = delegate { };
        public event EventHandler OnPostCollectionChanged = delegate { };

        public new bool Add(T item)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            bool results = base.Add(item);
            OnPostCollectionChanged(this, EventArgs.Empty);

            return results;
        }

        public new void Clear()
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.Clear();
            OnPostCollectionChanged(this, EventArgs.Empty);
        }

        public new bool Remove(T item)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            bool results = base.Remove(item);
            OnPostCollectionChanged(this, EventArgs.Empty);

            return results;
        }

        public new int RemoveWhere(Predicate<T> match)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            int results = base.RemoveWhere(match);
            OnPostCollectionChanged(this, EventArgs.Empty);

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
