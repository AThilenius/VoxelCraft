using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct GuiRectVerticie
    {
        public ushort PositionX;
        public ushort PositionY;
        public ushort PositionZ;
        public byte R;
        public byte G;
        public byte B;
        public byte A;
        private ushort _Padding;

        public GuiRectVerticie(Point pt, Color color)
        {
            PositionX = (ushort)pt.X;
            PositionY = (ushort)pt.Y;
            R = (byte)color.R;
            G = (byte)color.G;
            B = (byte)color.B;
            A = (byte)color.A;

            PositionZ = 0;
            _Padding = 0;
        }
    }

    public static class Gui
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiSetScale(float scale);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiResetDepth();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawRectangle(Rectangle rect, Color color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawEllipse( Point centroid, int width, int height, Color top, Color bottom );

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiAddVerticie(GuiRectVerticie vert);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawImage(string path, Rectangle frame);

        #endregion

        public static float Scale
        {
            get { return m_scale; }
            set
            {
                m_scale = value;
                m_inverseScale = 1.0f / value;
                VCInteropGuiSetScale(value);
            }
        }
        private static float m_scale = 1.0f;
        private static float m_inverseScale = 1.0f / m_scale;

        static Gui()
        {
            Scale = 1.5f;
            Window.TrueSize = Window.TrueSize * Scale;
        }

        public static void DrawRectangle(Rectangle rect, Color color)
        {
            VCInteropGuiDrawRectangle(rect, color);
        }

        public static void DrawBorderedRect(Rectangle rect, Color back, Color border, int borderWidth)
        {
            // Background
            if (back != Color.Trasparent)
                Gui.DrawRectangle(new Rectangle(rect.X, rect.Y, rect.Width, rect.Height), back);

            // Left
            Gui.DrawRectangle(new Rectangle(rect.X, rect.Y, borderWidth, rect.Height), border);

            // Bottom
            Gui.DrawRectangle(new Rectangle(rect.X, rect.Y, rect.Width, borderWidth), border);

            // Top
            Gui.DrawRectangle(new Rectangle(rect.X, rect.Y + rect.Height - borderWidth, rect.Width, borderWidth), border);

            // Right
            Gui.DrawRectangle(new Rectangle(rect.X + rect.Width - borderWidth, rect.Y, borderWidth, rect.Height), border);
        }

        public static void DrawButton(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(233, 233, 233, 255), new Color(183, 183, 183, 255));
            DrawBorder(rect, upperBar, lowerBar, new Color(153, 153, 153, 255));
        }

        public static void DrawButtonAccentuated(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(236, 238, 249, 255), new Color(183, 193, 211, 255));
            DrawBorder(rect, upperBar, lowerBar, new Color(153, 153, 153, 255));
        }

        public static void DrawButtonHighlighted(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(145, 163, 180, 255), new Color(82, 109, 132, 255));
            // Blue Border
            DrawBorder(rect, upperBar, lowerBar, new Color(82, 109, 132, 255));
        }

        public static void DrawBackgroundEmpty(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(217, 222, 229, 255), new Color(210, 216, 224, 255));
            DrawBorder(rect, upperBar, lowerBar, new Color(153, 153, 153, 255));
        }

        public static void DrawBackground(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(231, 234, 239, 255), new Color(224, 229, 234, 255));
            DrawBorder(rect, upperBar, lowerBar, new Color(153, 153, 153, 255));
        }

        private static void DrawDualToneVertical(Rectangle rect, Color upper, Color lower)
        {
            GuiRectVerticie ll = new GuiRectVerticie(new Point(rect.X, rect.Y), lower);
            GuiRectVerticie ul = new GuiRectVerticie(new Point(rect.X, rect.Y + rect.Height), upper);

            GuiRectVerticie lr = new GuiRectVerticie(new Point(rect.X + rect.Width, rect.Y), lower);
            GuiRectVerticie ur = new GuiRectVerticie(new Point(rect.X + rect.Width, rect.Y + rect.Height), upper);

            Gui.AddVerticie(ul);
            Gui.AddVerticie(ll);
            Gui.AddVerticie(lr);

            Gui.AddVerticie(ul);
            Gui.AddVerticie(lr);
            Gui.AddVerticie(ur);
        }

        private static void DrawBorder(Rectangle rect, Boolean upperBar, Boolean lowerBar, Color color)
        {
            if (upperBar)
                Gui.DrawRectangle(new Rectangle(rect.X, rect.Y + rect.Height - 1, rect.Width, 1), color);

            if (lowerBar)
                Gui.DrawRectangle(new Rectangle(rect.X, rect.Y, rect.Width, 1), color);

            Gui.DrawRectangle(new Rectangle(rect.X, rect.Y, 1, rect.Height), color);
            Gui.DrawRectangle(new Rectangle(rect.X + rect.Width - 1, rect.Y, 1, rect.Height), color);
        }

        public static void DrawEllipse(Point centroid, int width, int height, Color color)
        {
            VCInteropGuiDrawEllipse(centroid, width, height, color, color);
        }

        public static void AddVerticie(GuiRectVerticie vert)
        {
            VCInteropGuiAddVerticie(vert);
        }

        public static void DrawNormalizedRectangle(RectangleF rect, Color color)
        {
            int x = (int) Math.Round(Window.ScaledSize.X * rect.X);
            int y = (int) Math.Round(Window.ScaledSize.Y * rect.Y);
            int width = (int) Math.Round(Window.ScaledSize.X * rect.Width);
            int height = (int) Math.Round(Window.ScaledSize.Y * rect.Height);

            DrawRectangle(new Rectangle(x, y, width, height), color);
        }

        public static void DrawImage(string path, Rectangle frame, bool absolutePath = false)
        {
            if (!absolutePath)
            {
                string absp = Path.Combine(PathUtilities.ImagesPath, path);
                TestFileExistance(absp);
                VCInteropGuiDrawImage(absp, frame);
            }

            else
            {
                TestFileExistance(path);
                VCInteropGuiDrawImage(path, frame);
            }
        }

        private static bool TestFileExistance(string fullPath)
        {
            if (!File.Exists(fullPath))
            {
                Console.WriteLine("Cannot find file: " + fullPath);
                Console.ReadLine();
                return false;
            }

            return true;
        }


        internal static void Reset()
        {
            VCInteropGuiResetDepth();
        }
    }
}
