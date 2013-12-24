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
        extern static int VCInteropGetShaderFromFile(String name);

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

        #endregion

        public static List<Shader> Shaders = new List<Shader>();

        public String Name;

        public List<ShaderAttribute> Attributes = new List<ShaderAttribute>();
        public List<ShaderUniform> Uniforms = new List<ShaderUniform>();

        public String VertexShader = "";
        public String GeometryShader = "";
        public String FragmentShader = "";

        private Shader(int handle) : base(handle)
        {
        }

        public static void LoadAllShaders()
        {
            //foreach (FileInfo info in (new DirectoryInfo(PathUtilities.ShadersPath)).GetFiles())
            //{
            //    if (info.Extension != ".vcshader")
            //        continue;
                
            //    int uHandle = VCInteropGetShaderFromFile(Path.GetFileNameWithoutExtension(info.Name));

            //    Shader shader = new Shader(uHandle);
            //    using (TextReader reader = new StreamReader(info.FullName))
            //        JsonConvert.PopulateObject(reader.ReadToEnd(), shader);

            //    Shaders.Add(shader);
            //}
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
