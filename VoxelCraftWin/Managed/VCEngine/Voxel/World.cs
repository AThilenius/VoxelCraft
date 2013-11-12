using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Ubyte4
    {
        public Ubyte4 (byte x, byte y, byte z, byte w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        public byte X;
        public byte Y;
        public byte Z;
        public byte W;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Block
    {
        public static Block Empty { get { return new Block(0, 0, 0, 0); } }

        public Color Color;

        public Block(int r, int g, int b, int a)
        {
            Color = new Color(r, g, b, a);
        }

        public Block(Color color)
        {
            Color = color;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VCWorldRebuildParams
    {
        public bool ShowShadows;
        public bool ForceRebuildAll;

        public VCWorldRebuildParams(bool showShadows, bool forceRebuild)
        {
            ShowShadows = showShadows;
            ForceRebuildAll = forceRebuild;
        }
    }

    public class World : MarshaledObject
    {
        #region Bindings


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static int VCInteropNewWorld();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropReleaseWorld(int handle);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static int VCInteropWorldGetCamera(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldSetGenerator(int wHandle, int cHandle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldSetViewDist(int handle, int distance);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldInitializeEmpty(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldGenerateRegenerate(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldRebuild(int handle, VCWorldRebuildParams param);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldSaveToFile(int handle, string path);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldLoadFromFile(int handle, string path);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static Block VCInteropWorldGetBlock(int handle, int x, int y, int z);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldSetBlock(int handle, int x, int y, int z, Block block);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static int VCInteropWorldRaycast(int handle, Ray ray, out RaycastHit hitOut);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewWorld; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseWorld; } }

        #endregion

        public Camera Camera;
        public VCWorldRebuildParams RebuildParams = new VCWorldRebuildParams(true, false);
        public IChunkGenerator Generator
        {
            get
            {
                return m_generator;
            }

            set
            {
                m_generator = value;
                VCInteropWorldSetGenerator(UnManagedHandle, ((MarshaledObject) value).UnManagedHandle);
            }
        }
        public int ViewDistance
        {
            get
            {
                return m_viewDistance;
            }

            set
            {
                m_viewDistance = value;
                VCInteropWorldSetViewDist(UnManagedHandle, value);
            }
        }

        private IChunkGenerator m_generator;
        private int m_viewDistance = 0;

        public void Initialize()
        {
            VCInteropWorldInitializeEmpty(UnManagedHandle);
            Camera = new Camera(VCInteropWorldGetCamera(UnManagedHandle));
        }

        public void GenerateRegenerate()
        {
            VCInteropWorldGenerateRegenerate(UnManagedHandle);
        }

        public void SaveToFile(string path)
        {
            VCInteropWorldSaveToFile(UnManagedHandle, path);
        }

        public void LoadFromFile(string path)
        {
            VCInteropWorldLoadFromFile(UnManagedHandle, path);
        }

        public void ReBuild()
        {
            VCInteropWorldRebuild(UnManagedHandle, RebuildParams);
            RebuildParams.ForceRebuildAll = false;
        } 

        public Block GetBlock(int x, int y, int z)
        {
            return VCInteropWorldGetBlock(UnManagedHandle, x, y, z);
        }
        public Block GetBlock(float x, float y, float z)
        {
            return VCInteropWorldGetBlock(UnManagedHandle, (int)Math.Floor(x), (int)Math.Floor(y), (int)Math.Floor(z));
        }
        public Block GetBlock(Vector3 position)
        {
            return VCInteropWorldGetBlock(UnManagedHandle, (int)Math.Floor(position.X), (int)Math.Floor(position.Y), (int)Math.Floor(position.Z));
        }

        public void SetBlock(Location location, Block block)
        {
            VCInteropWorldSetBlock(UnManagedHandle, location.X, location.Y, location.Z, block);
        }

        public void SetBlock(int x, int y, int z, Block block)
        {
            VCInteropWorldSetBlock(UnManagedHandle, x, y, z, block);
        }

        public void SetBlock(float x, float y, float z, Block block)
        {
            VCInteropWorldSetBlock(UnManagedHandle, (int)Math.Floor(x), (int)Math.Floor(y), (int)Math.Floor(z), block);
        }

        public void SetBlock(Vector3 position, Block block)
        {
            VCInteropWorldSetBlock(UnManagedHandle, (int)Math.Floor(position.X), (int)Math.Floor(position.Y), (int)Math.Floor(position.Z), block);
        }

        public static Location[] GetBlocksInRegion (Location from, Location to)
        {
            int minX = Math.Min(from.X, to.X);
            int maxX = Math.Max(from.X, to.X);
            int minY = Math.Min(from.Y, to.Y);
            int maxY = Math.Max(from.Y, to.Y);
            int minZ = Math.Min(from.Z, to.Z);
            int maxZ = Math.Max(from.Z, to.Z);

            // Can optimize by pre computing array size.
            List<Location> locs = new List<Location>();

            for (int z = minZ; z <= maxZ; z++)
            {
                for (int x = minX; x <= maxX; x++)
                {
                    for (int y = minY; y <= maxY; y++)
                    {
                        locs.Add(new Location(x, y, z));
                    }
                }
            }

            return locs.ToArray();
        }

        public static Location[] GetBlocksInSphere(Location centroid, float radius)
        {
            List<Location> locs = new List<Location>();
            Vector3 centroidF = new Vector3(centroid);
            int radiusi = (int)radius;

            for (int z = centroid.Z - radiusi; z < centroid.Z + (radiusi * 2); z++)
            {
                for (int x = centroid.X - radiusi; x < centroid.X + (radiusi * 2); x++)
                {
                    for (int y = centroid.Y - radiusi; y < centroid.Y + (radiusi * 2); y++)
                    {
                        // Distance test
                        Vector3 thisLoc = new Vector3(x, y, z);
                        if ((thisLoc - centroidF).LengthFast <= radius)
                            locs.Add(new Location(x, y, z));
                    }
                }
            }

            return locs.ToArray();
        }

        public bool Raycast(Ray ray, out RaycastHit hit)
        {
            RaycastHit newHit = new RaycastHit();
            bool result = VCInteropWorldRaycast(UnManagedHandle, ray, out newHit) > 0;
            hit = newHit;

            return result;
        }

    }
}
