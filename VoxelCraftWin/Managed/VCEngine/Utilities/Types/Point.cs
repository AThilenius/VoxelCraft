using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Point : IAnimatable
    {
        public int X;
        public int Y;

        public Point(int x, int y)
        {
            X = x;
            Y = y;
        }

        public Point(Vector2 vec2)
        {
            X = (int)vec2.X;
            Y = (int)vec2.Y;
        }

        public override string ToString()
        {
            return "[ " + X + ", " + Y + " ]";
        }

        public static int Distance(Point p1, Point p2)
        {
            return (int) Math.Sqrt((p1.X - p2.X) * (p1.X - p2.X) + (p1.X - p2.X) * (p1.X - p2.X));
        }

        public static Point operator +(Point p1, Point p2)
        {
            return new Point(p1.X + p2.X, p1.Y + p2.Y);
        }

        public static Point operator -(Point p1, Point p2)
        {
            return new Point(p1.X - p2.X, p1.Y - p2.Y);
        }

        public static Point operator *(Point rect, float scale)
        {
            return new Point(
                (int)(rect.X * scale),
                (int)(rect.Y * scale));
        }

        public static Point operator /(Point rect, float scale)
        {
            return new Point(
                (int)(rect.X / scale),
                (int)(rect.Y / scale));
        }

        public static Point Lerp(Point a, Point b, float ammount)
        {
            return new Point((int)(ammount * (b.X - a.X) + a.X), (int)(ammount * (b.Y - a.Y) + a.Y));
        }

        public IAnimatable Lerp(IAnimatable from, IAnimatable to, float ammount)
        {
            return Point.Lerp((Point)from, (Point)to, ammount);
        }
    }
}
