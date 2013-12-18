using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class FlatChunkGenerator : MarshaledObject, IChunkGenerator
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropNewFlatGenerator();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropReleaseFlatGenerator(int handle);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewFlatGenerator; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseFlatGenerator; } }

        #endregion

    }
}
