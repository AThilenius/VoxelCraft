using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ShaderAttribute
    {

        public enum AttributeTypes
        {
            Position0 = 0,
            Position1 = 1,
            Normal0 = 2,
            Normal1 = 3,
            Color0 = 4,
            Color1 = 5,
            TexCoord0 = 6,
            TexCoord1 = 7,
            Flags0 = 8,
            Flags1 = 9,
            Tangent0 = 10,
            Tangent1 = 11,
            BiTangent0 = 12,
            BiTangent1 = 13,
        }

        [JsonConverter(typeof(StringEnumConverter))]
        public AttributeTypes AttributeType;

        public String Name;

    }
}
