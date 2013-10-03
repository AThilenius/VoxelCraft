using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ObservableList<T> : List<T>
    {

        public event EventHandler OnPreCollectionChanged = delegate { };
        public event EventHandler OnPostCollectionChanged = delegate { };

        public T this[int index]
        {
            get { return base[index]; }
            set
            {
                OnPreCollectionChanged(this, EventArgs.Empty);
                base[index] = value;
                OnPostCollectionChanged(this, EventArgs.Empty);
            }
        }

        public void Add(T item)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.Add(item);
            OnPostCollectionChanged(this, EventArgs.Empty);
        }

        public void AddRange(IEnumerable<T> collection)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.AddRange(collection);
            OnPostCollectionChanged(this, EventArgs.Empty);
        }

        public void Clear()
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.Clear();
            OnPostCollectionChanged(this, EventArgs.Empty);
        }

        public void Insert(int index, T item)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.Insert(index, item);
            OnPostCollectionChanged(this, EventArgs.Empty);
        }

        public void InsertRange(int index, IEnumerable<T> collection)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.InsertRange(index, collection);
            OnPostCollectionChanged(this, EventArgs.Empty);
        }

        public bool Remove(T item)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            bool result = base.Remove(item);
            OnPostCollectionChanged(this, EventArgs.Empty);

            return result;
        }

        public int RemoveAll(Predicate<T> match)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            int result = base.RemoveAll(match);
            OnPostCollectionChanged(this, EventArgs.Empty);

            return result;
        }

        public void RemoveAt(int index)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.RemoveAt(index);
            OnPostCollectionChanged(this, EventArgs.Empty);
        }

        public void RemoveRange(int index, int count)
        {
            OnPreCollectionChanged(this, EventArgs.Empty);
            base.RemoveRange(index, count);
            OnPostCollectionChanged(this, EventArgs.Empty);
        }


    }
}
