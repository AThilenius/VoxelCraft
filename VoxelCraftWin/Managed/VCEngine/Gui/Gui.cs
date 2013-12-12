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
        public byte R;
        public byte G;
        public byte B;
        public byte A;

        public GuiRectVerticie(Point pt, Color color)
        {
            PositionX = (ushort)pt.X;
            PositionY = (ushort)pt.Y;
            R = (byte)color.R;
            G = (byte)color.G;
            B = (byte)color.B;
            A = (byte)color.A;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct TextMetrics
    {
        public int TotalWidth;
        public int TotalHeight;

        public TextMetrics(int width, int height)
        {
            TotalWidth = width;
            TotalHeight = height;
        }
    }

    public class Gui
    {
        public static string ResourcesFolder { get { return Path.Combine(Environment.CurrentDirectory, @"Resources"); } }
        public static string ImagesFolder { get { return Path.Combine(ResourcesFolder, @"Images"); } }


        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawRectangle(Rectangle rect, Color color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawEllipse( Point centroid, int width, int height, Color top, Color bottom );

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawText(int font, string text, Point point, Color color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiGetTextMetrics(int font, string text, out TextMetrics metrics);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static string VCInteropLoadFont(string fntPath, string ddsPath, out int fontId);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiAddVerticie(GuiRectVerticie vert);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawImage(string path, Rectangle frame);

        #endregion

        private static Dictionary<String, int> m_fontIDs = new Dictionary<String, int>();

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

        public static void DrawString(string text, Point llPoint, Color color, string font = "Calibri-16")
        {
            VCInteropGuiDrawText(m_fontIDs[font], text, new Point(llPoint.X, llPoint.Y + 16), color);
        }

        public static TextMetrics GetMetrics(string text, string font = "Calibri-16")
        {
            TextMetrics tm;
            VCInteropGuiGetTextMetrics(m_fontIDs[font], text, out tm);
            return tm;
        }

        public static void LoadFontsFromForlder(string folder)
        {
            string[] fntFiles = Directory.GetFiles(folder, "*.fnt", SearchOption.AllDirectories);

            foreach (String str in fntFiles)
            {
                string dir = Path.GetDirectoryName(str);
                string file = Path.GetFileNameWithoutExtension(str);
                string ddsFile = Path.Combine(dir, file + "_0.DDS");

                if (!File.Exists(ddsFile))
                {
                    Console.WriteLine("Cannot find .DDS file for fnt : + file");
                    continue;
                }

                int fontId;
                String fontName = VCInteropLoadFont(str, ddsFile, out fontId);
                m_fontIDs.Add(fontName, fontId);

                Console.WriteLine("Loaded font: " + fontName);
            }
        }

        public static void DrawNormalizedRectangle(RectangleF rect, Color color)
        {
            int x = (int) Math.Round(Window.Size.X * rect.X);
            int y = (int) Math.Round(Window.Size.Y * rect.Y);
            int width = (int) Math.Round(Window.Size.X * rect.Width);
            int height = (int) Math.Round(Window.Size.Y * rect.Height);

            DrawRectangle(new Rectangle(x, y, width, height), color);
        }

        public static void DrawImage(string path, Rectangle frame, bool absolutePath = false)
        {
            if (!absolutePath)
            {
                string absp = Path.Combine(ImagesFolder, path);
                TestFileExistance(absp);
                VCInteropGuiDrawImage(absp, frame);
            }

            else
            {
                TestFileExistance(path);
                VCInteropGuiDrawImage(path, frame);
            }
        }

        public static void PreUpdate()
        {

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

    }
}
