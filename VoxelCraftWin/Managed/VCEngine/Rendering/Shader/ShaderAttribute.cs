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
            Position0   = 0,
            Position1   = 1,
            Position2   = 2,
            Position3   = 3,
            Position4   = 4,
            Normal0     = 5,
            Normal1     = 6,
            Normal2     = 7,
            Normal3     = 8,
            Normal4     = 9,
            Color0      = 10,
            Color1      = 11,
            Color2      = 12,
            Color3      = 13,
            Color4      = 14,
            TexCoord0   = 15,
            TexCoord1   = 16,
            TexCoord2   = 17,
            TexCoord3   = 18,
            TexCoord4   = 19,
            Flags0      = 20,
            Flags1      = 21,
            Flags2      = 22,
            Flags3      = 23,
            Flags4      = 24
        }

        [JsonConverter(typeof(StringEnumConverter))]
        public AttributeTypes AttributeType;

        public String Name;

    }
}
