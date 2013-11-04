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

        public override string ToString()
        {
            return
                "[ Origin: " + Origin.X + " | " + Origin.Y + " | " + Origin.Z + " ]" +
                "[ Direction: " + Direction.X + " | " + Direction.Y + " | " + Direction.Z + " ]" +
                "[ MaxDistance: " + MaxDistance + " ]";
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct RaycastHit
    {
        public float Distance;
        public byte Type;
        public Vector3 Normal;
        public Location CubeLocation;

        public override string ToString()
        {
            return
                "[ Distance: " + Distance + " ] " +
                "[ At: " + CubeLocation.X + " | " + CubeLocation.Y + " | " + CubeLocation.Z + " ]" +
                "[ Type: " + Type + " ]" +
                "[ Normal: " + Normal.X + " | " + Normal.Y + " | " + Normal.Z + " ]";
        }
    }

    //public static class Physics
    //{
    //    #region Bindings

    //    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    //    extern static bool VCInteropPhysicsRaycastWorld(Ray ray, ref RaycastHit hitOut);

    //    #endregion

    //    public static bool Raycast(Ray ray, out RaycastHit hit)
    //    {
    //        RaycastHit newHit = new RaycastHit();
    //        bool result = VCInteropPhysicsRaycastWorld(ray, ref newHit);
    //        hit = newHit;

    //        return result;
    //    }

    //}
}
