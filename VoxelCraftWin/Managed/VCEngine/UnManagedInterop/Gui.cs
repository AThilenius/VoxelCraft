using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace VCEngine
{
    public class Gui
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiClear();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawRectangle(Rectangle rect, Color color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawText(string font, string text, Point point, Color color);

        #endregion

        public static void Clear()
        {
            VCInteropGuiClear();
        }

        public static void DrawRectangle(Rectangle rect, Color color)
        {
            VCInteropGuiDrawRectangle(rect, color);
        }

        public static void DrawString(string text, Point llPoint, Color color, string font = "Cambria-32")
        {
            VCInteropGuiDrawText(font, text, llPoint, color);
        }
        

    }
}
