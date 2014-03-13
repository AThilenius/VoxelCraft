using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ConsoleFunction : Attribute
    {
        public String Name;
        public String Brief;
        public String Catagory;

        public ConsoleFunction(String brief)
        {
            Brief = brief;
            Catagory = "";
        }

        public ConsoleFunction(String brief, String catagory)
        {
            Brief = brief;
            Catagory = catagory;
        }

    }
}
