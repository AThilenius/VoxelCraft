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

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropPhysicsPxSceneAddActor(int handle, int actorHandle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropPhysicsPxSceneSimulate(int handle, double deltaTime);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropPhysicsPxSceneNew; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropPhysicsPxSceneRelease; } }

        #endregion

        public void AddActor(PxRigidActor actor)
        {
            VCInteropPhysicsPxSceneAddActor(UnManagedHandle, actor.UnManagedHandle);
        }

        public void Simulate()
        {
            VCInteropPhysicsPxSceneSimulate(UnManagedHandle, Time.DeltaTime);
        }

    }
}
