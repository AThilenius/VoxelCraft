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
