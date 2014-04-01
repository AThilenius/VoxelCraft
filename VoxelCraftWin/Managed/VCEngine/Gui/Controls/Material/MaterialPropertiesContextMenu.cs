using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialPropertiesContextMenu : ContextMenu
    {
        private Material m_boundMaterial = null;
        private String m_boundMaterialPath;

        public MaterialPropertiesContextMenu(Window window) : base(window)
        {
        }

        public void ChangeShaderType(Shader newShader)
        {
            if (m_boundMaterial == null)
                throw new Exception("Cannot change the shader type of a material without a bound material");

            // Set the Shader type
            m_boundMaterial.Shader = newShader.Name;

            // Re-Open the material ( Will prune fields automatically )
            OpenMaterial(m_boundMaterial, m_boundMaterialPath);
        }

        public void OpenMaterial(Material material, String path)
        {
            m_boundMaterial = material;
            m_boundMaterialPath = path;
            m_orderedControlList.Clear();

            Shader shader = Shader.GetByName(material.Shader);

            // Add missing types to the Material
            foreach (ShaderUniform shaderUniform in shader.Uniforms)
            {
                // If the material doesn't have a definition for this type, create one
                if (material.UniformValues.Where(val => val.Name == shaderUniform.Name && val.Type == shaderUniform.ValueType).Count() == 0)
                    material.UniformValues.Add(new Material.MaterialUniformValue(shaderUniform));
            }

            // List = List where
            material.UniformValues = material.UniformValues.Where(

                // The Shader DOES have that Name/Type ( AKA. Remove unneeded material definitions )
                unifValue => shader.Uniforms.Where(unif => unif.Name == unifValue.Name && unif.ValueType == unifValue.Type).Count() != 0).ToList();

            // Create an editor for each Material UniformValue
            foreach (Material.MaterialUniformValue uniformValue in material.UniformValues)
            {
                UniformEditor unifEditor = UniformTypeFactory.GetEditor(ParentWindow, uniformValue);
                AddIContextComponent(unifEditor);

                unifEditor.OnUniformChanged += (s, a) =>
                    {
                        uniformValue.Value = a.NewUniformValue;

                        // Re-Serialize / Save
                        String newJson = JsonConvert.SerializeObject(material, Formatting.Indented);
                        File.WriteAllText(path, newJson);

                        // Force the engine to reload it
                        Material.ForceReload(path);
                    };
            }

            // Force a Re-Save
            File.WriteAllText(path, JsonConvert.SerializeObject(material, Formatting.Indented));

            // Force the engine to reload it
            Material.ForceReload(path);
        }



    }
}
