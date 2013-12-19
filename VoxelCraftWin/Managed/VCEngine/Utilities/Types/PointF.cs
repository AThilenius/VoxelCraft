using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct PointF
    {
        public float X;
        public float Y;

        public PointF(float x, float y)
        {
            X = x;
            Y = y;
        }
    }
}
