using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct RectangleF
    {
        public float X;
        public float Y;
        public float Width;
        public float Height;

        public RectangleF(float x, float y, float width, float height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }

        public static RectangleF operator *(RectangleF rect, float scale)
        {
            return new RectangleF(
                rect.X * scale,
                rect.Y * scale,
                rect.Width * scale,
                rect.Height * scale);
        }

        public static RectangleF operator /(RectangleF rect, float scale)
        {
            return new RectangleF(
                rect.X / scale,
                rect.Y / scale,
                rect.Width / scale,
                rect.Height / scale);
        }
    }
}
