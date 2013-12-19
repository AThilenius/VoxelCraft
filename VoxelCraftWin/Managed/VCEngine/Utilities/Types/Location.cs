using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Location
    {
        public int X;
        public int Y;
        public int Z;

        public Location(int x, int y, int z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public Location(Vector3 v)
        {
            X = (int)v.X;
            Y = (int)v.Y;
            Z = (int)v.Z;
        }
    }
}
