using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Ray
    {
        public Vector3 Origin;
        public Vector3 Direction;
        public float MaxDistance;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct RaycastHit
    {
        public double Distance;
        public byte Type;
        Vector3 Normal;
        int X;
        int Y;
        int Z;

        public override string ToString()
        {
            return
                "[ Distance: " + Distance + " ] " +
                "[ At: " + X + " | " + Y + " | " + Z + " ]" +
                "[ Type: " + Type + " ]" +
                "[ Normal: " + Normal.X + " | " + Normal.Y + " | " + Normal.Z + " ]";
        }
    }

    public static class Physics
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static bool VCInteropPhysicsRaycastWorld(Ray ray, ref RaycastHit hitOut);

        #endregion

        public static bool Raycast(Ray ray, out RaycastHit hit)
        {
            RaycastHit newHit = new RaycastHit();
            bool result = VCInteropPhysicsRaycastWorld(ray, ref newHit);
            hit = newHit;

            return result;
        }

    }
}
