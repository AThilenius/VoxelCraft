using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class PxRigidStatic : PxRigidActor
    {

        #region Bindings
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropPhysicsRigidStaticCreate(Vector3 pos, Quaternion quat);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCINteropPhysicsRigidStaticRelease(int handle);

        // Custom CTor
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCINteropPhysicsRigidStaticRelease; } }

        #endregion

        public PxRigidStatic(Vector3 pos, Quaternion rot)
        {
            UnManagedHandle = VCInteropPhysicsRigidStaticCreate(pos, rot);
            ObjectStore.RegisterObject(this, UnManagedHandle);
        }

    }
}
