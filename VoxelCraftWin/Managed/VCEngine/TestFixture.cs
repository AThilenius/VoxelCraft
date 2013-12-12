using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TestFixture
    {

        internal static void OnStart()
        {
            Font.GetFont("Calibri", 8);
        }

        public static void PerUpdate()
        {

        }

        public static void LatePerUpdate()
        {
            //Font.GetFont("Berlin Sans FB", 64).DrawString("The quick brown fox jumps over the lazy dog", new Point(10, 110), Color.Black);
            //Font.GetFont("Berlin Sans FB", 32).DrawString("The quick brown fox jumps over the lazy dog", new Point(10, 140), Color.Black);
            //Font.GetFont("Bradley Hand ITC", 32).DrawString("The quick brown fox jumps over the lazy dog", new Point(10, 170), Color.Black);
            //Font.GetFont("Calibri", 16).DrawString("The quick brown fox jumps over the lazy dog", new Point(10, 200), Color.Black);
            //Font.GetFont("Calibri", 24).DrawString("The quick brown fox jumps over the lazy dog", new Point(10, 230), Color.Black);
        }


    }
}
