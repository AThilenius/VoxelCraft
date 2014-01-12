using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class PxRigidDynamic : PxRigidActor
    {

        #region Bindings
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropPhysicsRigidDynamicCreate(Vector3 pos, Quaternion quat);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCINteropPhysicsRigidDynamicRelease(int handle);

        // Custom CTor
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCINteropPhysicsRigidDynamicRelease; } }

        #endregion

        public PxRigidDynamic(Vector3 pos, Quaternion rot)
        {
            UnManagedHandle = VCInteropPhysicsRigidDynamicCreate(pos, rot);
            ObjectStore.RegisterObject(this, UnManagedHandle);
        }

    }
}
