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
        public Block(int r, int g, int b, int a)
        {
            Color = new Color(r, g, b, a);
        }

        public Block(Color color)
        {
            Color = color;
        }

        public Color Color;
    }

    public class World : MarshaledObject
    {
        #region Bindings


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static int VCInteropNewWorld();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropReleaseWorld(int handle);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldSetGenerator(int wHandle, int cHandle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldSetViewDist(int handle, int distance);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldInitialize(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldGenerateRegenerate(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldRebuild(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static Block VCInteropWorldGetBlock(int handle, int x, int y, int z);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropWorldSetBlock(int handle, int x, int y, int z, Block block);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static int VCInteropWorldRaycast(int handle, Ray ray, out RaycastHit hitOut);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewWorld; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseWorld; } }

        #endregion

        private IChunkGenerator m_generator;
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

        private int m_viewDistance = 0;
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

        public void Initialize()
        {
            VCInteropWorldInitialize(UnManagedHandle);
        }

        public void GenerateRegenerate()
        {
            VCInteropWorldGenerateRegenerate(UnManagedHandle);
        }

        public void ReBuild()
        {
            VCInteropWorldRebuild(UnManagedHandle);
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

        public bool Raycast(Ray ray, out RaycastHit hit)
        {
            RaycastHit newHit = new RaycastHit();
            bool result = VCInteropWorldRaycast(UnManagedHandle, ray, out newHit) > 0;
            hit = newHit;

            return result;
        }

    }
}
