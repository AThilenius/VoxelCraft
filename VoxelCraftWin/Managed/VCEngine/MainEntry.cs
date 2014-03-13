using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VCEngine
{
    public class MainEntry
    {

        public static void Main()
        {
            Task.Factory.StartNew(() =>
                {
                    while (true)
                    {
                        Console.WriteLine("Got: " + Console.ReadLine());
                    }
                });
            Editor.EditorMain();
        }

    }
}
