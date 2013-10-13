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

    public class Gui
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiClear();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawRectangle(Rectangle rect, Color color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawText(string font, string text, Point point, Color color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static string VCInteropLoadFont(string fntPath, string ddsPath);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiAddVerticie(GuiRectVerticie vert);

        #endregion

        public static void Clear()
        {
            VCInteropGuiClear();
        }

        public static void DrawRectangle(Rectangle rect, Color color)
        {
            VCInteropGuiDrawRectangle(rect, color);
        }

        public static void DrawBorderedRect(Rectangle rect, Color back, Color border, int borderWidth)
        {
            // Background
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

        public static void AddVerticie(GuiRectVerticie vert)
        {
            VCInteropGuiAddVerticie(vert);
        }

        public static void DrawString(string text, Point llPoint, Color color, string font = "Calibri-16")
        {
            VCInteropGuiDrawText(font, text, new Point(llPoint.X, llPoint.Y + 16), color);
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

                Console.WriteLine("Loaded font: " + VCInteropLoadFont(str, ddsFile));
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

        public static void PreUpdate()
        {
            Gui.Clear();
        }

    }
}
