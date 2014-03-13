using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct GuiVerticie
    {
        public Vector3 Position;
        public Vector2 UV;
        public Ubyte4 Color;

        public GuiVerticie(Vector3 pos, Vector2 uv, Ubyte4 color)
        {
            Position = pos;
            UV = uv;
            Color = color;
        }

    }
}
