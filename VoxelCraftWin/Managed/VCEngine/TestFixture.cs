using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TestFixture
    {

        internal static void OnStart()
        {
            String vert = 
@"
This is some
multi line
{
    test code with
    variable indentation
}
";
            //Shader testShader = new Shader { Name = "ShaderName", VertexShader = vert, FragmentShader = vert };

            //testShader.Attributes.Add(new ShaderAttribute { AttributeType = ShaderAttribute.AttributeTypes.Position0, Name = "PositionIn" });
            //testShader.Attributes.Add(new ShaderAttribute { AttributeType = ShaderAttribute.AttributeTypes.Color0, Name = "ColorIn" });
            //testShader.Attributes.Add(new ShaderAttribute { AttributeType = ShaderAttribute.AttributeTypes.Normal0, Name = "NormalIn" });

            //testShader.Uniforms.Add(new ShaderUniform { ValueType = ShaderUniform.ValueTypes.Matrix4, Name = "InverseLightMatrix" });
            //testShader.Uniforms.Add(new ShaderUniform { ValueType = ShaderUniform.ValueTypes.Sampler2D, Name = "DiffuseTexture" });
            //testShader.Uniforms.Add(new ShaderUniform { ValueType = ShaderUniform.ValueTypes.Sampler2D, Name = "NormalTexture" });

            //using (TextWriter writer = new StreamWriter(@"JsonOutput.txt"))
            //{
            //    writer.Write(JsonConvert.SerializeObject(testShader, Formatting.Indented));
            //}

            //using (TextReader reader = new StreamReader(@"JsonOutput.txt"))
            //{
            //    Shader shader = JsonConvert.DeserializeObject<Shader>(reader.ReadToEnd());
            //}
        }

        public static void PerUpdate()
        {
        }

        public static void LatePerUpdate()
        {
        }


    }
}
