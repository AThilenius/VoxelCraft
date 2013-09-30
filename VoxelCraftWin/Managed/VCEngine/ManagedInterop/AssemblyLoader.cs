using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;

namespace VCEngine
{
    internal static class AssemblyLoader
    {
        internal static Assembly BoundAssembly;

        // Static Instances
        public static List<StaticInstance> StaticInstances = new List<StaticInstance>();

        internal static void UseAssembly(string path)
        {
            BoundAssembly = Assembly.LoadFrom(path);

            if (BoundAssembly == null)
            {
                Console.WriteLine("Failed to load assembly: " + path);
                return;
            }

            var staticInstDerivedTypes = BoundAssembly.GetTypes().Where(x => x.IsSubclassOf(typeof(StaticInstance)));

            foreach (Type type in staticInstDerivedTypes)
            {
                StaticInstance inst = Activator.CreateInstance(type) as StaticInstance;
                StaticInstances.Add(inst);
            }

        }
    }
}
