using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class PxScene : MarshaledObject
    {

        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropPhysicsPxSceneNew();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropPhysicsPxSceneRelease(int handle);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropPhysicsPxSceneNew; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropPhysicsPxSceneRelease; } }

        #endregion

    }
}
