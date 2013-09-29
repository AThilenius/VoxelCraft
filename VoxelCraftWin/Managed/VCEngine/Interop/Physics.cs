using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct RaycastHit
    {
        public bool DidHit;
        public double Distance;
        public int WorldX;
        public int WorldY;
        public int WorldZ;

        public override string ToString()
        {
            return 
                "[ Did Hit: " + DidHit + " ] " +
                "[ Distance: " + Distance + " ] " +
                "[ At: " + WorldX + " | " + WorldY + " | " + WorldZ + " ]";
        }
    }

    public static class Physics
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropPhysicsRaycastWorld(ref RaycastHit hitOut);

        #endregion

        public static bool Raycast(out RaycastHit hit)
        {
            RaycastHit newHit = new RaycastHit();
            VCInteropPhysicsRaycastWorld(ref newHit);
            hit = newHit;

            return newHit.DidHit;
        }

    }
}
