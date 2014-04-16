using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    enum GLPrimitives : int
    {
	    Byte                    = 0,
	    UnsignedByte            = 1,
	    Short                   = 2,
	    UnsignedShort           = 3,
	    Int                     = 4,
	    UnsignedInt             = 5,
	    Float                   = 6,
	    Byte2                   = 7,
	    Byte3                   = 8,
	    Byte4                   = 9,
	    Double                  = 10
    };

    enum GLDrawModes : int
    {
	    Static                  = 0,
	    Dynamic                 = 1,
	    Stream                  = 2
    };

    enum GLDrawPrimitives : int
    {
        Points                  = 0, 
        LineStrip               = 1, 
        LineLoop                = 2, 
        LInes                   = 3, 
        LineStripAdjaceny       = 4, 
        LinesAdjacency          = 5, 
        TriangleStrip           = 6, 
        TriangleFan             = 7, 
        Triangles               = 8, 
        TriangleStripAdjacency  = 9, 
        TrianglesAdjacency      = 10,
        Patches                 = 11
    };

    /// <summary>
    /// Facade interface for a VCGLMarshaledBuffer, wrapping a VCGLBuffer VAO/VBO combo
    /// </summary>
    public class GLBuffer : MarshaledObject
    {

        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropGLBufferCreate();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGLBufferRelease(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropGLBufferDraw(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropVCGLBufferSetVertexData(int handle, UInt32 size, IntPtr data, int count, GLDrawModes drawMode);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropVCGLBufferSetDrawPrimitiveType(int handle, GLDrawPrimitives primitiveType);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropVCGLBufferSetVertexAttribute(int handle, 
														  ShaderAttribute attribType, 
														  int count, 
														  GLPrimitives primitiveType, 
														  bool normalize, 
														  int strideSize, 
														  int offset);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static  void VCInteropVCGLBufferSetVertexAttributeI(int handle, 
														   ShaderAttribute attribType, 
														   int count, 
														   GLPrimitives primitiveType, 
														   int strideSize, 
														   int offset);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static  void VCInteropVCGLBUfferSetIndexBuffer(int handle, 
													  int size, 
													  IntPtr data, 
													  int count, 
													  GLPrimitives indecieType, 
													  GLDrawModes drawMode);


        protected virtual UnManagedCTorDelegate UnManagedCTor { get { return VCInteropGLBufferCreate; } }
        protected virtual UnManagedDTorDelegate UnManagedDTor { get { return VCInteropGLBufferRelease; } }

        #endregion

        /// <summary>
        /// Facade interface to mimic the fluent API used in the unmanaged class VCGLBuffer
        /// </summary>
        public class VertexSpecification
        {
            private GLBuffer m_buffer;

            public VertexSpecification(GLBuffer buffer)
            {
                m_buffer = buffer;
            }

	        /// Malloc / Memcpy to GPU memory
            VertexSpecification SetVertexData(UInt32 size, IntPtr data, int count, GLDrawModes drawMode = GLDrawModes.Static)
            {
                VCInteropVCGLBufferSetVertexData(m_buffer.UnManagedHandle, size, data, count, drawMode);
                return this;
            }

	        /// Specify a non-integral type attribute ( floating point based )
            VertexSpecification SetVertexAttribute(ShaderAttribute attribType, int count, GLPrimitives primitiveType, bool normalize, int strideSize, int offset)
            {
                VCInteropVCGLBufferSetVertexAttribute(m_buffer.UnManagedHandle, attribType, count, primitiveType, normalize, strideSize, offset);
                return this;
            }

	        /// Specify an integral type attribute ( Integer based )
            VertexSpecification SetVertexAttributeI(ShaderAttribute attribType, int count, GLPrimitives primitiveType, int strideSize, int offset)
            {
                VCInteropVCGLBufferSetVertexAttributeI(m_buffer.UnManagedHandle, attribType, count, primitiveType, strideSize, offset);
                return this;
            }
        }

        private VertexSpecification m_vboSpec;

        public GLBuffer()
        {
            m_vboSpec = new VertexSpecification(this);
        }

        /// Binds the VAO and invokes glDrawElements or glDrawArrays.
        void Draw()
        {
            VCInteropGLBufferDraw(UnManagedHandle);
        }

	    /// Access point for all vertex attribute buffer specification
        VertexSpecification VertexBufferSpecification(GLDrawPrimitives drawPrimitiveType = GLDrawPrimitives.Triangles)
        {
            VCInteropVCGLBufferSetDrawPrimitiveType(UnManagedHandle, drawPrimitiveType);
            return m_vboSpec;
        }

	    /// Direct Index buffer setup
        void IndexBufferSpecification(int size, IntPtr data, int count, GLPrimitives indecieType = GLPrimitives.UnsignedInt, GLDrawModes drawMode = GLDrawModes.Static)
        {
            VCInteropVCGLBUfferSetIndexBuffer(UnManagedHandle, size, data, count, indecieType, drawMode);
        }

    }
}
