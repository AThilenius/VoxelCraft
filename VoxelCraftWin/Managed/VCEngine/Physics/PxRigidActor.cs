using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public abstract class PxRigidActor : MarshaledObject
    {

        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropPhysicsRigidActorAttachShape(int handle, int shapeHandle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static Vector3 VCInteropPhysicsRigidActorGetPosition(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static Quaternion VCInteropPhysicsRigidActorGetRotation(int handle);

        // Abstract, overloaded by children
        //protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropPhysicsPxSceneNew; } }
        //protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropPhysicsShapeRelease; } }

        #endregion

        public void AttachShape(PxShape shape)
        {
            VCInteropPhysicsRigidActorAttachShape(UnManagedHandle, shape.UnManagedHandle);
        }

        public Vector3 GetPosition()
        {
            return VCInteropPhysicsRigidActorGetPosition(UnManagedHandle);
        }

        public Quaternion GetRotation()
        {
            return VCInteropPhysicsRigidActorGetRotation(UnManagedHandle);
        }

    }
}
