using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace VCEngine
{
    public class World
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static int VCInteropWorldGetBlock(int x, int y, int z);

        #endregion

        public static int GetBlock(int x, int y, int z)
        {
            return VCInteropWorldGetBlock(x, y, z);
        }

        public static int GetBlock(float x, float y, float z)
        {
            return VCInteropWorldGetBlock((int)Math.Floor(x), (int)Math.Floor(y), (int)Math.Floor(z));
        }

        public static int GetBlock(Vector3 position)
        {
            return VCInteropWorldGetBlock((int) Math.Floor(position.X), (int) Math.Floor(position.Y), (int) Math.Floor(position.Z));
        }

    }
}
