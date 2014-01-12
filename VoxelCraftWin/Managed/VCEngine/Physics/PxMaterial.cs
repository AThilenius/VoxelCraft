using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class PxMaterial : MarshaledObject
    {

        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropPhysicsPxMaterialNew();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropPhysicsPXMaterialRelease(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropPhysicsPxMaterialInitialize(int handle, float staticFriction, float dynamicFriction, float restitution);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropPhysicsPxMaterialNew; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropPhysicsPXMaterialRelease; } }

        #endregion

        public PxMaterial(float staticFriction, float dynamicFriction, float restitution) : base()
        {
            VCInteropPhysicsPxMaterialInitialize(UnManagedHandle, staticFriction, dynamicFriction, restitution);
        }

    }
}
