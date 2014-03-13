using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace VCEngine
{
    public static class ConsoleFunctionLoader
    {
        private class ConsoleFunctionInstance
        {
            public ConsoleFunction Attribute;
            public MethodInfo Method;
        }

        private static Dictionary<String, ConsoleFunctionInstance> m_consoleFunctions = new Dictionary<String, ConsoleFunctionInstance>();

        public static void AddAssembly(Assembly assembly)
        {
            // Get all methods marked with ConsoleFunction Attribute
            MethodInfo[] methods = assembly.GetTypes()
                      .SelectMany(t => t.GetMethods())
                      .Where(m => m.GetCustomAttributes(typeof(ConsoleFunction), false).Length > 0)
                      .ToArray();

            // Build Dictionary from method names, delimit class names
            foreach (MethodInfo mInfo in methods)
            {
                ConsoleFunction cFun = (ConsoleFunction)mInfo.GetCustomAttributes(typeof(ConsoleFunction), false)[0];
                String path = (cFun.Catagory.Length == 0 || cFun.Catagory.EndsWith(".")) ? cFun.Catagory.ToLower() + mInfo.Name.ToLower() : cFun.Catagory.ToLower() + "." + mInfo.Name.ToLower();
                cFun.Name = (cFun.Catagory.Length == 0 || cFun.Catagory.EndsWith(".")) ? cFun.Catagory + mInfo.Name : cFun.Catagory + "." + mInfo.Name;
                m_consoleFunctions.Add(path, new ConsoleFunctionInstance { Attribute = cFun, Method = mInfo });
            }
        }

        public static void AsyncListen()
        {
            Task.Factory.StartNew(() =>
                {

                    while (true)
                    {
                        String commandText = Console.ReadLine();
                        String[] subStrs = commandText.Split(' ');
                        Object[] args = { subStrs };

                        if (!m_consoleFunctions.ContainsKey(subStrs[0].ToLower()))
                            Console.WriteLine("Failed to find command: " + subStrs[0]);

                        else
                        {
                            ConsoleFunctionInstance cfInst = m_consoleFunctions[subStrs[0].ToLower()];
                            cfInst.Method.Invoke(null, args);
                        }
                    }

                });
        }

        // Help Loader
        [ConsoleFunction("This will never be displayed for help")]
        public static void Help(String[] args)
        {
            Console.WriteLine("All known functions:");

            foreach (ConsoleFunctionInstance inst in m_consoleFunctions.Values)
                if (inst.Attribute.Name.ToLower() != "help")
                    Console.WriteLine("  - {0,-20} : {1,-40}", inst.Attribute.Name, inst.Attribute.Brief);
        }

    }
}
