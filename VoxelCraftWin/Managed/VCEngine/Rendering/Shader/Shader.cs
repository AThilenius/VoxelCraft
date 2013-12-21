using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class Shader : MarshaledObject
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropShaderNew();
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderRelease(int handle);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetStrings(int handle, String name, String vertShader, String geometryShader, String fragmentShader);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderAddUniform(int handle, int typeId, String name);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderAddAttribute(int handle, int id, String name);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderCompile(int handle);



        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformInt(int handle, int index, int value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformFloat(int handle, int index, float value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformVec2(int handle, int index, Vector2 value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformVec3(int handle, int index, Vector3 value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformVec4(int handle, int index, Vector4 value);

        //[DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        //extern static void VCInteropShaderSetUniformMat3(int handle, int index, Matrix3 value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformMat4(int handle, int index, Matrix4 value);

        protected override MarshaledObject.UnManagedCTorDelegate UnManagedCTor { get { return VCInteropShaderNew; } }
        protected override MarshaledObject.UnManagedDTorDelegate UnManagedDTor { get { return VCInteropShaderRelease; } }

        #endregion

        public String Name;

        public List<ShaderAttribute> Attributes = new List<ShaderAttribute>();
        public List<ShaderUniform> Uniforms = new List<ShaderUniform>();

        public String VertexShader = "";
        public String GeometryShader = "";
        public String FragmentShader = "";

        public static Shader LoadFromFile (String name)
        {
            Shader shader = new Shader();
            using (TextReader reader = new StreamReader(name))
                JsonConvert.PopulateObject(reader.ReadToEnd(), shader);

            VCInteropShaderSetStrings(shader.UnManagedHandle, shader.Name, shader.VertexShader, shader.GeometryShader, shader.FragmentShader);

            foreach (ShaderAttribute atrib in shader.Attributes)
                VCInteropShaderAddAttribute(shader.UnManagedHandle, (int)atrib.AttributeType, atrib.Name);

            foreach (ShaderUniform unif in shader.Uniforms)
                VCInteropShaderAddUniform(shader.UnManagedHandle, (int)unif.ValueType, unif.Name);

            VCInteropShaderCompile(shader.UnManagedHandle);

            return shader;
        }

        public static Shader[] LoadAllShaders()
        {
            List<Shader> shaders = new List<Shader>();

            foreach (FileInfo info in (new DirectoryInfo(PathUtilities.ShadersPath)).GetFiles())
                if (info.Extension == ".vcshader")
                    shaders.Add(LoadFromFile(info.FullName));

            return shaders.ToArray();
        }

        public void SetUniform(int index, int value)
        {
            VCInteropShaderSetUniformInt(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, float value)
        {
            VCInteropShaderSetUniformFloat(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, Vector2 value)
        {
            VCInteropShaderSetUniformVec2(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, Vector3 value)
        {
            VCInteropShaderSetUniformVec3(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, Vector4 value)
        {
            VCInteropShaderSetUniformVec4(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, Matrix4 value)
        {
            VCInteropShaderSetUniformMat4(UnManagedHandle, index, value);
        }

    }
}
