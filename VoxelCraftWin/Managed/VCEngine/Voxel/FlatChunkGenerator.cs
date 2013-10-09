using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace VCEngine
{
    public class FlatChunkGenerator : MarshaledObject, IChunkGenerator
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static int VCInteropNewFlatGenerator();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropReleaseFlatGenerator(int handle);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewFlatGenerator; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseFlatGenerator; } }

        #endregion

    }
}
