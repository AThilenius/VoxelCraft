using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ShaderUniform
    {

        public enum ValueTypes
        {
            Float       = 0,
            Int         = 1,
            Vector2     = 2,
            Vector3     = 3,
            Vector4     = 4,
            Matrix3     = 5,
            Matrix4     = 6,
            ColorRGBA   = 7,
            Sampler2D   = 8,
            Sampler3D   = 9
        }

        [JsonConverter(typeof(StringEnumConverter))]
        public ValueTypes ValueType;

        public String Name;

    }
}
