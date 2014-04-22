using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class DualKeyDictionary<K1, K2, V>
    {
        public Dictionary<K1, V> KeyOneDictionary = new Dictionary<K1, V>();
        public Dictionary<K2, V> KeyTwoDictionary = new Dictionary<K2, V>();
        
        public delegate K1 KeyOneGenerator(V val);
        public delegate K2 KeyTwoGenerator(V val);

        public DualKeyDictionary()
        {

        }

        public DualKeyDictionary(V[] source, KeyOneGenerator keyOneGenerator, KeyTwoGenerator keyTwoGenerator)
        {
            if (source == null)
                return;

            foreach (V val in source)
            {
                KeyOneDictionary.Add(keyOneGenerator(val), val);
                KeyTwoDictionary.Add(keyTwoGenerator(val), val);
            }
        }

        public void Add(K1 keyOne, K2 keyTwo, V value)
        {
            KeyOneDictionary.Add(keyOne, value);
            KeyTwoDictionary.Add(keyTwo, value);
        }

        public void Remove(K1 keyOne, K2 keyTwo)
        {
            KeyOneDictionary.Remove(keyOne);
            KeyTwoDictionary.Remove(keyTwo);
        }

        public V this[K1 keyOne]
        {
            get { return KeyOneDictionary[keyOne]; }
            set { KeyOneDictionary[keyOne] = value; }
        }

        public V this[K2 keyTwo]
        {
            get { return KeyTwoDictionary[keyTwo]; }
            set { KeyTwoDictionary[keyTwo] = value; }
        }

        public Boolean ContainsKey(K1 keyOne)
        {
            return KeyOneDictionary.ContainsKey(keyOne);
        }

        public Boolean ContainsKey(K2 keyTwo)
        {
            return KeyTwoDictionary.ContainsKey(keyTwo);
        }
    }
}
