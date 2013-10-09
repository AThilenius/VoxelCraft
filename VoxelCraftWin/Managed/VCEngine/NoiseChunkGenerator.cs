using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace VCEngine
{
    public class NoiseChunkGenerator : MarshaledObject, IChunkGenerator
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static int VCInteropNewNoiseGenerator();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropReleaseNoiseGenerator(int handle);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewNoiseGenerator; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseNoiseGenerator; } }

        #endregion

    }
}
