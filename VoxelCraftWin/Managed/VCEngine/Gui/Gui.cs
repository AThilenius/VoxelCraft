using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
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

    public enum AnimationScale
    {
        Linear,
        Trigonometric
    }

    public class Gui
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiSetScale(float scale);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiResetDepth();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiDrawRectangle(Rectangle rect, Color color);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiDrawEllipse( Point centroid, int width, int height, Color top, Color bottom );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiAddVerticie(GuiRectVerticie vert);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiDrawImage(string path, Rectangle frame);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiDraw9SliceImage(string path, Rectangle frame, int pizelOffset, float padding);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiDraw9SliceGui(string path, Color baseColor, Rectangle frame, int pizelOffset, float padding);

        #endregion

        public Window ParentWindow;
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
        private static float m_inverseScale;

        public Gui(Window window)
        {
            m_inverseScale = 1.0f / m_scale;
            ParentWindow = window;
            Scale = ParentWindow.MonitorSize.X > 1920 ? 1.5f : 1.0f;
            ParentWindow.TrueSize = ParentWindow.TrueSize * Scale;
        }

        #region Drawing

        public void DrawRectangle(Rectangle rect, Color color)
        {
            VCInteropGuiDrawRectangle(rect, color);
        }

        public void DrawBorderedRect(Rectangle rect, Color back, Color border, int borderWidth)
        {
            // Background
            if (back != Color.Trasparent)
                DrawRectangle(new Rectangle(rect.X, rect.Y, rect.Width, rect.Height), back);

            // Left
            DrawRectangle(new Rectangle(rect.X, rect.Y, borderWidth, rect.Height), border);

            // Bottom
            DrawRectangle(new Rectangle(rect.X, rect.Y, rect.Width, borderWidth), border);

            // Top
            DrawRectangle(new Rectangle(rect.X, rect.Y + rect.Height - borderWidth, rect.Width, borderWidth), border);

            // Right
            DrawRectangle(new Rectangle(rect.X + rect.Width - borderWidth, rect.Y, borderWidth, rect.Height), border);
        }

        public void DrawButton(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(233, 233, 233, 255), new Color(183, 183, 183, 255));
            DrawBorder(rect, upperBar, lowerBar, new Color(153, 153, 153, 255));
        }

        public void DrawButtonAccentuated(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(236, 238, 249, 255), new Color(183, 193, 211, 255));
            DrawBorder(rect, upperBar, lowerBar, new Color(153, 153, 153, 255));
        }

        public void DrawButtonHighlighted(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(145, 163, 180, 255), new Color(82, 109, 132, 255));
            // Blue Border
            DrawBorder(rect, upperBar, lowerBar, new Color(82, 109, 132, 255));
        }

        public void DrawBackgroundEmpty(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(217, 222, 229, 255), new Color(210, 216, 224, 255));
            DrawBorder(rect, upperBar, lowerBar, new Color(153, 153, 153, 255));
        }

        public void DrawBackground(Rectangle rect, Boolean upperBar = true, Boolean lowerBar = true)
        {
            DrawDualToneVertical(rect, new Color(231, 234, 239, 255), new Color(224, 229, 234, 255));
            DrawBorder(rect, upperBar, lowerBar, new Color(153, 153, 153, 255));
        }

        private void DrawDualToneVertical(Rectangle rect, Color upper, Color lower)
        {
            GuiRectVerticie ll = new GuiRectVerticie(new Point(rect.X, rect.Y), lower);
            GuiRectVerticie ul = new GuiRectVerticie(new Point(rect.X, rect.Y + rect.Height), upper);

            GuiRectVerticie lr = new GuiRectVerticie(new Point(rect.X + rect.Width, rect.Y), lower);
            GuiRectVerticie ur = new GuiRectVerticie(new Point(rect.X + rect.Width, rect.Y + rect.Height), upper);

            AddVerticie(ul);
            AddVerticie(ll);
            AddVerticie(lr);

            AddVerticie(ul);
            AddVerticie(lr);
            AddVerticie(ur);
        }

        private void DrawBorder(Rectangle rect, Boolean upperBar, Boolean lowerBar, Color color)
        {
            if (upperBar)
                DrawRectangle(new Rectangle(rect.X, rect.Y + rect.Height - 1, rect.Width, 1), color);

            if (lowerBar)
                DrawRectangle(new Rectangle(rect.X, rect.Y, rect.Width, 1), color);

            DrawRectangle(new Rectangle(rect.X, rect.Y, 1, rect.Height), color);
            DrawRectangle(new Rectangle(rect.X + rect.Width - 1, rect.Y, 1, rect.Height), color);
        }

        public void DrawEllipse(Point centroid, int width, int height, Color color)
        {
            VCInteropGuiDrawEllipse(centroid, width, height, color, color);
        }

        public void AddVerticie(GuiRectVerticie vert)
        {
            VCInteropGuiAddVerticie(vert);
        }

        public void DrawNormalizedRectangle(RectangleF rect, Color color)
        {
            int x = (int)Math.Round(ParentWindow.ScaledSize.X * rect.X);
            int y = (int)Math.Round(ParentWindow.ScaledSize.Y * rect.Y);
            int width = (int)Math.Round(ParentWindow.ScaledSize.X * rect.Width);
            int height = (int)Math.Round(ParentWindow.ScaledSize.Y * rect.Height);

            DrawRectangle(new Rectangle(x, y, width, height), color);
        }

        public void DrawImage(string path, Rectangle frame, bool absolutePath = false)
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

        public void Draw9SliceImage(string path, Rectangle frame, int pizelOffset = 4, float padding = 0.25f, bool absolutePath = false)
        {
            if (!absolutePath)
            {
                string absp = Path.Combine(PathUtilities.ImagesPath, path);
                TestFileExistance(absp);
                VCInteropGuiDraw9SliceImage(absp, frame, (int)Math.Round(pizelOffset * Scale), padding);
            }

            else
            {
                TestFileExistance(path);
                VCInteropGuiDraw9SliceImage(path, frame, (int)Math.Round(pizelOffset * Scale), padding);
            }
        }

        public void Draw9SliceGui(string path, Color baseColor, Rectangle frame, int pizelOffset = 5, float padding = 0.25f, bool absolutePath = false)
        {
            if (!absolutePath)
            {
                string absp = Path.Combine(PathUtilities.ImagesPath, path);
                TestFileExistance(absp);
                VCInteropGuiDraw9SliceGui(absp, baseColor, frame, pizelOffset, padding);
            }

            else
            {
                TestFileExistance(path);
                VCInteropGuiDraw9SliceGui(path, baseColor, frame, pizelOffset, padding);
            }
        }

        #endregion
        
        #region Misc

        private bool TestFileExistance(string fullPath)
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

        #endregion
    }
}
