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
        public static Color ControlDisabled { get { return new Color(246, 242, 246, 255); } }
        public static Color ControlDisabledText { get { return new Color(173, 164, 177, 255); } }
        public static Color ControlLightBackground { get { return new Color(246, 246, 246, 255); } }
        public static Color ControlMediumBackground { get { return new Color(239, 239, 242, 255); } }
        public static Color ControlDark { get { return new Color(136, 136, 136, 255); } }
        public static Color ControlVeryDark { get { return new Color(66, 66, 66, 255); } }
        public static Color ControlBorder { get { return Color.ControlBlue; } }
        public static Color ControlBlue { get { return new Color(0, 122, 204, 255); } }
        public static Color ControlGreen { get { return new Color(55, 138, 55, 255); } }
        public static Color ControlRed { get { return new Color(157, 36, 12, 255); } }
        public static Color Trasparent { get { return new Color(0, 0, 0, 0); } }


        public static Color Lerp(Color from, Color to, float ammount)
        {
            return new Color(
                (int)(from.R + (to.R - from.R) * ammount),
                (int)(from.G + (to.G - from.G) * ammount),
                (int)(from.B + (to.B - from.B) * ammount),
                (int)(from.A + (to.A - from.A) * ammount));
        }

        /// <summary>
        /// Converts an HSL color value to RGB.
        /// Input: Vector4 ( X: [0.0, 1.0], Y: [0.0, 1.0], Z: [0.0, 1.0], W: [0.0, 1.0] )
        /// Output: Color ( R: [0, 255], G: [0, 255], B: [0, 255], A: [0, 255] )
        /// </summary>
        /// <param name="hsl">Vector4 defining X = h, Y = s, Z = l, W = a. Ranges [0, 1.0]</param>
        /// <returns>RGBA Color. Ranges [0, 255]</returns>
        public static Color HslToRgba(Vector4 hsl)
        {
            float r, g, b;

            if (hsl.Y == 0.0f)
                r = g = b = hsl.Z;

            else
            {
                var q = hsl.Z < 0.5f ? hsl.Z * (1.0f + hsl.Y) : hsl.Z + hsl.Y - hsl.Z * hsl.Y;
                var p = 2.0f * hsl.Z - q;
                r = HueToRgb(p, q, hsl.X + 1.0f / 3.0f);
                g = HueToRgb(p, q, hsl.X);
                b = HueToRgb(p, q, hsl.X - 1.0f / 3.0f);
            }

            return new Color((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(hsl.W * 255));
        }

        // Helper for HslToRgba
        private static float HueToRgb(float p, float q, float t)
        {
            if (t < 0.0f) t += 1.0f;
            if (t > 1.0f) t -= 1.0f;
            if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
            if (t < 1.0f / 2.0f) return q;
            if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
            return p;
        }

        /// <summary>
        /// Converts an RGB color value to HSL.
        /// Input: Color ( R: [0, 255], G: [0, 255], B: [0, 255], A: [0, 255] )
        /// Output: Vector4 ( X: [0.0, 1.0], Y: [0.0, 1.0], Z: [0.0, 1.0], W: [0.0, 1.0] )
        /// </summary>
        /// <param name="rgba"></param>
        /// <returns></returns>
        public static Vector4 RgbaToHsl(Color rgba)
        {
            float r = rgba.R / 255.0f;
            float g = rgba.G / 255.0f;
            float b = rgba.B / 255.0f;

            float max = (r > g && r > b) ? r : (g > b) ? g : b;
            float min = (r < g && r < b) ? r : (g < b) ? g : b;

            float h, s, l;
            h = s = l = (max + min) / 2.0f;

            if (max == min)
                h = s = 0.0f;

            else
            {
                float d = max - min;
                s = (l > 0.5f) ? d / (2.0f - max - min) : d / (max + min);

                if (r > g && r > b)
                    h = (g - b) / d + (g < b ? 6.0f : 0.0f);

                else if (g > b)
                    h = (b - r) / d + 2.0f;

                else
                    h = (r - g) / d + 4.0f;

                h /= 6.0f;
            }

            return new Vector4(h, s, l, rgba.A / 255.0f);
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            Color p = (Color)obj;
            return
                R == p.R &&
                G == p.G &&
                B == p.B &&
                A == p.A;
        }

        public override string ToString()
        {
            return "[ RGBa: " + R + ", " + G + ", " + B + ", " + A + " ]";
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
