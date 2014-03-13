using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public static class GeneralConsoleFunctions
    {

        [ConsoleFunction("Clears the Console.")]
        public static String Cls(String[] args)
        {
            Console.Clear();
            return "";
        }

    }
}
