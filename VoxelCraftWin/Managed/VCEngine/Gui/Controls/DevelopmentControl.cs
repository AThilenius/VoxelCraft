using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct TextureVerticie
    {
        public Vector3 Position;
        public Vector2 UV;
    }

    public class DevelopmentControl : Control
    {
        private Shader m_shader;
        private Texture m_texture;
        private GLBuffer m_vbo;
    

        public unsafe DevelopmentControl(Window window)
            : base(window)
        {
            m_shader = Shader.GetByPath(@"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\VoxelCraftWin\Resources\Shaders\TexturePassThrough." + PathUtilities.ShaderExtension);
            m_texture = Texture.Get(@"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\VoxelCraftWin\Assets\Textures\Sunset.jpg", Resources.LoadType.Immediate);
            m_vbo = new GLBuffer();

            // Create a triangle array
            TextureVerticie[] data = {
                                         new TextureVerticie { Position = new Vector3(0, 0, -1), UV = new Vector2(0, 1) },
                                         new TextureVerticie { Position = new Vector3(1, 0, -1), UV = new Vector2(1, 1) },
                                         new TextureVerticie { Position = new Vector3(0, 1, -1), UV = new Vector2(0, 0) }
                                     };

            // Setup the VBO
            int sizeOfVert = Marshal.SizeOf(typeof(TextureVerticie));

            fixed(TextureVerticie* ptr = &data[0])
            {
                m_vbo.VertexBufferSpecification(GLDrawPrimitives.Triangles)
                    .SetVertexAttribute(ShaderAttribute.AttributeTypes.Position0, 3, GLPrimitives.Float, false, sizeOfVert, 0)
                    .SetVertexAttribute(ShaderAttribute.AttributeTypes.TexCoord0, 2, GLPrimitives.Float, false, sizeOfVert, 12)
                    .SetVertexData((uint)(sizeOfVert * 3), (IntPtr) ptr, 3);
            }

        }

        protected override void Draw()
        {
            base.Draw();

            // Try to draw our image
            m_texture.Bind(0);
            m_shader.Bind();
            m_shader.SetModelMatrix(Matrix4.CreateOrthographicOffCenter(0, 1, 0, 1, 0.01f, 100));
            m_vbo.Draw();
        }

    }
}
