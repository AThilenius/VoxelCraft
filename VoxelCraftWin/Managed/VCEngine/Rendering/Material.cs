using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System;
using System.Collections.Generic;
using System.IO;
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

            // Used by JSON only
            private MaterialUniformValue()
            { 
            }

            // Create a default one
            public MaterialUniformValue(ShaderUniform unifType)
            {
                Name = unifType.Name;
                Type = unifType.ValueType;
                Value = Material.MaterialUniformValue.GetDefaultValue(unifType.ValueType);
            }

            public MaterialUniformValue(String name, ShaderUniform.ValueTypes type, String value)
            {
                Name = name;
                Type = type;
                Value = value;
            }

            public static String GetDefaultValue(ShaderUniform.ValueTypes type)
            {
                switch (type)
                {
                    case ShaderUniform.ValueTypes.Float: return "1.0";
                    case ShaderUniform.ValueTypes.Int: return "0";
                    case ShaderUniform.ValueTypes.Vector2: return "0.0 : 0.0";
                    case ShaderUniform.ValueTypes.Vector3: return "0.0 : 0.0 : 0.0";
                    case ShaderUniform.ValueTypes.Vector4: return "0.0 : 0.0 : 0.0 : 0.0";
                    case ShaderUniform.ValueTypes.Matrix3: return "1.0 : 0.0 : 0.0 : 0.0 : 1.0 : 0.0 : 0.0 : 0.0 : 1.0";
                    case ShaderUniform.ValueTypes.Matrix4: return "1.0 : 0.0 : 0.0 : 0.0 : 0.0 : 1.0 : 0.0 : 0.0 : 0.0 : 0.0 : 1.0 : 0.0 : 0.0 : 0.0 : 0.0 : 1.0";
                    case ShaderUniform.ValueTypes.ColorRGBA: return "127 : 127 : 127 : 255";
                    case ShaderUniform.ValueTypes.Sampler2D: return "";
                    case ShaderUniform.ValueTypes.Sampler3D: return "";
                    default: throw new Exception("Unknown ShaderUniform Type!");
                }
            }

        }

        public String Name;
        public String Shader;
        public List<MaterialUniformValue> UniformValues = new List<MaterialUniformValue>();

        public static void ForceReload(String path)
        {
            VCInteropResourceManagerReloadMaterial(path);
        }

        public static Material Get(String fullPath)
        {
            return JsonConvert.DeserializeObject<Material>(File.ReadAllText(fullPath));
        }

    }
}
