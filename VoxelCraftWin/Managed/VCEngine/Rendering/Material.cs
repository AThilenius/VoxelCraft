using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class Material
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropResourceManagerReloadMaterial(String fullPath);

        #endregion

        public class MaterialUniformValue
        {
            [JsonConverter(typeof(StringEnumConverter))]
            public ShaderUniform.ValueTypes Type;
            public String Name;
            public String Value;

            public MaterialUniformValue(String name, ShaderUniform.ValueTypes type, String value)
            {
                Name = name;
                Type = type;
                Value = value;
            }

        }

        public String Name;
        public String Shader;
        public List<MaterialUniformValue> UniformValues = new List<MaterialUniformValue>();

        public static void ForceReload(String path)
        {
            VCInteropResourceManagerReloadMaterial(path);
        }

    }
}
