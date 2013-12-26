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
            Material testMat = new Material();
            testMat.Name = "Gun Textured";
            testMat.Shader = "DiffuseNormal";
            testMat.UniformValues.Add(new Material.MaterialUniformValue("Diffuse", ShaderUniform.ValueTypes.Sampler2D, @"C:\Users\BlahBlah\Gun.DDS"));
            testMat.UniformValues.Add(new Material.MaterialUniformValue("Normal", ShaderUniform.ValueTypes.Sampler2D, @"C:\Users\BlahBlah\GunNORM.DDS"));
            testMat.UniformValues.Add(new Material.MaterialUniformValue("NoiseScaler", ShaderUniform.ValueTypes.Float, @"1.0"));

            using (TextWriter writer = new StreamWriter(@"JsonOutput.txt"))
            {
                writer.Write(JsonConvert.SerializeObject(testMat, Formatting.Indented));
            }

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
