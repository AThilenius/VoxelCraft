using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public enum AnimationScale
    {
        Linear,
        Trigonometric
    }

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

    public class StandardTextures
    {
        public Texture Button = Texture.GetInResources(@"Images\Icons\Button.DDS");
        public Texture ButtonDown = Texture.GetInResources(@"Images\Icons\ButtonDown.DDS");
        public Texture ButtonHighlight = Texture.GetInResources(@"Images\Icons\ButtonHeighlight.DDS");
        public Texture ButtonHighlightDown = Texture.GetInResources(@"Images\Icons\ButtonHighlightDown.DDS");
        public Texture RoundButton = Texture.GetInResources(@"Images\Icons\RoundButton.DDS");
        public Texture RountButtonDown = Texture.GetInResources(@"Images\Icons\RoundButtonDown.DDS");

        public Texture TriButtonLeft = Texture.GetInResources(@"Images\Icons\ThreeButtonLeftUnpressed.DDS");
        public Texture TriButtonLeftHighlight = Texture.GetInResources(@"Images\Icons\ThreeButtonLeftHightlight.DDS");
        public Texture TriButtonLeftDown = Texture.GetInResources(@"Images\Icons\ThreeButtonLeftPressed.DDS");

        public Texture TriButtonCenter = Texture.GetInResources(@"Images\Icons\ThreeButtonCenterUnpressed.DDS");
        public Texture TriButtonCenterheightlight = Texture.GetInResources(@"Images\Icons\ThreeButtonCenterHightlight.DDS");
        public Texture TriButtonCenterDown = Texture.GetInResources(@"Images\Icons\ThreeButtonCenterPressed.DDS");

        public Texture TriButtonRight = Texture.GetInResources(@"Images\Icons\ThreeButtonRightUnpressed.DDS");
        public Texture TriButtonRightHighlight = Texture.GetInResources(@"Images\Icons\ThreeButtonRightHightlight.DDS");
        public Texture TriButtonRightDown = Texture.GetInResources(@"Images\Icons\ThreeButtonRightPressed.DDS");
    }

    public class GuiDrawer : MarshaledObject
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropGuiCreate();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiRelease(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiSetScale(int handle, float scale);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiRender(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiDrawRectangle(int handle, Rectangle rect, Color color);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiDrawEllipse(int handle, Point centroid, int width, int height, Color top, Color bottom);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiAddVerticie(int handle, GuiRectVerticie vert);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiDrawImage(int handle, int texHandle, Rectangle frame);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGuiDraw9SliceImage(int handle, int texHandle, Rectangle frame, int pizelOffset, float padding);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropGuiCreate; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropGuiRelease; } }

        #endregion

        public Window ParentWindow;
        public float Scale
        {
            get { return m_scale; }
            set
            {
                m_scale = value;
                m_inverseScale = 1.0f / value;
                VCInteropGuiSetScale(UnManagedHandle, value);
            }
        }
        public static StandardTextures StandardTextures = new StandardTextures();
        private float m_scale = 1.0f;
        private float m_inverseScale;

        public GuiDrawer(Window window)
        {
            m_inverseScale = 1.0f / m_scale;
            ParentWindow = window;
            Scale = Window.MonitorSize.X > 1920 ? 1.5f : 1.0f;
        }

        #region Drawing

        public void DrawRectangle(Rectangle rect, Color color)
        {
            VCInteropGuiDrawRectangle(UnManagedHandle, rect, color);
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
            VCInteropGuiDrawEllipse(UnManagedHandle, centroid, width, height, color, color);
        }

        public void AddVerticie(GuiRectVerticie vert)
        {
            VCInteropGuiAddVerticie(UnManagedHandle, vert);
        }

        public void DrawNormalizedRectangle(RectangleF rect, Color color)
        {
            int x = (int)Math.Round(ParentWindow.ScaledSize.X * rect.X);
            int y = (int)Math.Round(ParentWindow.ScaledSize.Y * rect.Y);
            int width = (int)Math.Round(ParentWindow.ScaledSize.X * rect.Width);
            int height = (int)Math.Round(ParentWindow.ScaledSize.Y * rect.Height);

            DrawRectangle(new Rectangle(x, y, width, height), color);
        }

        public void DrawImage(Texture texture, Rectangle frame)
        {
            VCInteropGuiDrawImage(UnManagedHandle, texture.UnManagedHandle, frame);
        }

        public void Draw9SliceImage(Texture texture, Rectangle frame, int pizelOffset = 4, float padding = 0.25f)
        {
            VCInteropGuiDraw9SliceImage(UnManagedHandle, texture.UnManagedHandle, frame, (int)Math.Round(pizelOffset * Scale), padding);
        }

        public void Draw9SliceGui(Texture texture, Color baseColor, Rectangle frame, int pizelOffset = 5, float padding = 0.25f)
        {
            //VCInteropGuiDraw9SliceGui(texture.UnManagedHandle, baseColor, frame, pizelOffset, padding);
        }

        #endregion
        
        #region Misc

        internal void Render()
        {
            VCInteropGuiRender(UnManagedHandle);
        }

        #endregion
    }
}
