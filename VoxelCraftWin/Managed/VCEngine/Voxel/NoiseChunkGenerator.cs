using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class NoiseChunkGenerator : MarshaledObject, IChunkGenerator
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropNewNoiseGenerator();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropReleaseNoiseGenerator(int handle);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewNoiseGenerator; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseNoiseGenerator; } }

        #endregion

    }
}
