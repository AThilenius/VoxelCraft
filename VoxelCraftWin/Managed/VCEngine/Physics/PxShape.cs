using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class PxShape : MarshaledObject
    {

        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropPhysicsBoxShapeNew(int materialHandle, Vector3 halfExtent);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropPhysicsCapsuleShapeNew(int materialHandle, float halfRadius, float halfHeight);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropPhysicsPlaneShapeNew(int materialHandle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropPhysicsSphereShapeNew(int materialHandle, float radius);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropPhysicsShapeRelease(int handle);

        // Custom CTor
        //protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropPhysicsPxSceneNew; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropPhysicsShapeRelease; } }

        #endregion

        // Use Factory Methods
        private PxShape(int handle)
        {
            UnManagedHandle = handle;
            ObjectStore.RegisterObject(this, UnManagedHandle);
        }

        public static PxShape CreateBoxShape(PxMaterial material, Vector3 halfExtent)
        {
            int unmanagedHandle = VCInteropPhysicsBoxShapeNew(material.UnManagedHandle, halfExtent);
            return new PxShape(unmanagedHandle);
        }

        public static PxShape CreateCapsuleShape(PxMaterial material, float halfRadius, float halfHeight)
        {
            int unmanagedHandle = VCInteropPhysicsCapsuleShapeNew(material.UnManagedHandle, halfRadius, halfHeight);
            return new PxShape(unmanagedHandle);
        }

        public static PxShape CreatePlaneShape(PxMaterial material)
        {
            int unmanagedHandle = VCInteropPhysicsPlaneShapeNew(material.UnManagedHandle);
            return new PxShape(unmanagedHandle);
        }

        public static PxShape CreateSphereShape(PxMaterial material, float radius)
        {
            int unmanagedHandle = VCInteropPhysicsSphereShapeNew(material.UnManagedHandle, radius);
            return new PxShape(unmanagedHandle);
        }

    }
}
