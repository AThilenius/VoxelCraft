using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public class Rectangle
    {
        public float X;
        public float Y;
        public float Width;
        public float Height;
    }
}
