using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ObservableList<T> : List<T>
    {

        public class AddRemoveEventArgs : EventArgs
        {
            public Boolean WasRemoved;
            public T Item;
        }

        public event EventHandler<AddRemoveEventArgs> OnCollectionChanged = delegate { };
        public event EventHandler OnClear = delegate { };

        new public T this[int index]
        {
            get { return base[index]; }
            set
            {
                base[index] = value;
                OnCollectionChanged(this, new AddRemoveEventArgs { WasRemoved = false, Item = value });
            }
        }

        new public void Add(T item)
        {
            base.Add(item);
            OnCollectionChanged(this, new AddRemoveEventArgs { WasRemoved = false, Item = item });
        }

        new public void AddRange(IEnumerable<T> collection)
        {
            throw new NotSupportedException();
        }

        new public void Clear()
        {
            throw new NotSupportedException();
        }

        new public void Insert(int index, T item)
        {
            base.Insert(index, item);
            OnCollectionChanged(this, new AddRemoveEventArgs { WasRemoved = false, Item = item });
        }

        new public void InsertRange(int index, IEnumerable<T> collection)
        {
            throw new NotSupportedException();
        }

        new public bool Remove(T item)
        {
            bool result = base.Remove(item);
            OnCollectionChanged(this, new AddRemoveEventArgs { WasRemoved = true, Item = item });

            return result;
        }

        new public int RemoveAll(Predicate<T> match)
        {
            throw new NotSupportedException();
        }

        new public void RemoveAt(int index)
        {
            T item = base[index];
            base.RemoveAt(index);
            OnCollectionChanged(this, new AddRemoveEventArgs { WasRemoved = true, Item = item });
        }

        new public void RemoveRange(int index, int count)
        {
            throw new NotSupportedException();
        }


    }
}
