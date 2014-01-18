using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Rectangle : IAnimatable
    {
        public int X;
        public int Y;
        public int Width;
        public int Height;

        public Rectangle(int x, int y, int width, int height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }

        public Rectangle(int x, int y, Point point)
        {
            X = x;
            Y = y;
            Width = point.X;
            Height = point.Y;
        }

        public Rectangle(Point point, int width, int height)
        {
            X = point.X;
            Y = point.Y;
            Width = width;
            Height = height;
        }

        public Rectangle(Point location, Point size)
        {
            X = location.X;
            Y = location.Y;
            Width = size.X;
            Height = size.Y;
        }

        public bool IsPointWithin(Point point)
        {
            return
                point.X >= X &&
                point.X <= X + Width &&
                point.Y >= Y &&
                point.Y <= Y + Height;
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            Rectangle p = (Rectangle)obj;
            return
                X == p.X &&
                Y == p.Y &&
                Width == p.Width &&
                Height == p.Height;
        }

        public static Rectangle operator *(Rectangle rect, float scale)
        {
            return new Rectangle(
                (int)(rect.X * scale),
                (int)(rect.Y * scale),
                (int)(rect.Width * scale),
                (int)(rect.Height * scale));
        }

        public static Rectangle operator /(Rectangle rect, float scale)
        {
            return new Rectangle(
                (int)(rect.X / scale),
                (int)(rect.Y / scale),
                (int)(rect.Width / scale),
                (int)(rect.Height / scale));
        }

        public static Rectangle operator +(Rectangle first, Rectangle second)
        {
            return new Rectangle(
                first.X + second.X,
                first.Y + second.Y,
                first.Width + second.Width,
                first.Height + second.Height);
        }

        public static Rectangle operator -(Rectangle first, Rectangle second)
        {
            return new Rectangle(
                first.X - second.X,
                first.Y - second.Y,
                first.Width - second.Width,
                first.Height - second.Height);
        }

        public static bool operator ==(Rectangle a, Rectangle b) { return a.Equals(b); }
        public static bool operator !=(Rectangle a, Rectangle b) { return !(a == b); }

        public override string ToString()
        {
            return "[ " + X + ", " + Y + " | " + Width + ", " + Height + " ]";
        }

        public static Rectangle Lerp(Rectangle from, Rectangle to, float ammount)
        {
            return new Rectangle(
                (int)(ammount * (to.X - from.X) + from.X), 
                (int)(ammount * (to.Y - from.Y) + from.Y), 
                (int)(ammount * (to.Width - from.Width) + from.Width),
                (int)(ammount * (to.Height - from.Height) + from.Height));
        }

        public IAnimatable Lerp(IAnimatable from, IAnimatable to, float ammount)
        {
            return Rectangle.Lerp((Rectangle)from, (Rectangle)to, ammount);
        }
    }
}
