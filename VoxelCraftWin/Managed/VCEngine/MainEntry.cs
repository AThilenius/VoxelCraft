using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace VCEngine
{
    public class MainEntry
    {
        public static void Main()
        {
            ConsoleFunctionLoader.RegisterUnManagedHooks();
            ConsoleFunctionLoader.AddAssembly(Assembly.GetExecutingAssembly());
            ConsoleFunctionLoader.AsyncListen();
            Editor.EditorMain();
        }

    }
}