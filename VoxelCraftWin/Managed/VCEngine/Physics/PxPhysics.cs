using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class PxPhysics
    {

        #region Bindings


        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropPhysicsInitializePhysXPhysics();

        #endregion

        public static void Initialize()
        {
            VCInteropPhysicsInitializePhysXPhysics();
        }

    }
}
