using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class InteropIn
    {
        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        [DllImport("VCEngine.UnManaged.exe")]
        public static extern void TestPInvoke();

        public static void EditorEntry()
        {
            Console.WriteLine("Editor Entry");
            TestPInvoke();
        }

        public static void TestWithInt(int val)
        {

        }
    }
}
