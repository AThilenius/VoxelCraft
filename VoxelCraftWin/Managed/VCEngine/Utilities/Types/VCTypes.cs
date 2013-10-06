using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Point
    {
        public int X;
        public int Y;

        public Point(int x, int y)
        {
            X = x;
            Y = y;
        }

        public override string ToString()
        {
            return "[ " + X + ", " + Y + " ]";
        }

        public static Point operator +(Point p1, Point p2)
        {
            return new Point(p1.X + p2.X, p1.Y + p2.Y);
        }

        public static Point operator -(Point p1, Point p2)
        {
            return new Point(p1.X - p2.X, p1.Y - p2.Y);
        }
    }

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

    [StructLayout(LayoutKind.Sequential)]
    public struct Color
    {
        public int R;
        public int G;
        public int B;
        public int A;

        public Color(int r, int g, int b, int a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }

        public static Color White { get { return new Color(255, 255, 255, 255); } }
        public static Color Black { get { return new Color(0, 0, 0, 255); } }
        public static Color ControlLight { get { return new Color(239, 239, 242, 255); } }
        public static Color ControlDisabled { get { return new Color(246, 242, 246, 255); } }
        public static Color ControlDark { get { return new Color(136, 136, 136, 255); } }
        public static Color ControlVeryDark { get { return new Color(66, 66, 66, 255); } }
        public static Color ControlBorder { get { return Color.ControlBlue; } }
        public static Color ControlBlue { get { return new Color(0, 122, 204, 255); } }
        public static Color ControlGreen { get { return new Color(55, 138, 55, 255); } }
        public static Color ControlRed { get { return new Color(157, 36, 12, 255); } }
        public static Color Trasparent { get { return new Color(0, 0, 0, 0); } }

        public bool Equals(Color p)
        {
            return 
                R == p.R &&
                G == p.G &&
                B == p.B &&
                A == p.A;
        }

        public static bool operator ==(Color a, Color b) { return a.Equals(b); }
        public static bool operator !=(Color a, Color b) { return !(a == b); }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Rectangle
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

        public bool IsPointWithin(Point point)
        {
            return
                point.X >= X &&
                point.X <= X + Width &&
                point.Y >= Y &&
                point.Y <= Y + Height;
        }

        public override string ToString()
        {
            return "[ " + X + ", " + Y + " | " + Width + ", " + Height + " ]";
        }
    }

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
    }
}
