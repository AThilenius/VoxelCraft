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
        public MaterialPropertiesContextMenu(Window window) : base(window)
        {
        }

        public void SetMaterial(Material material, String path)
        {
            m_orderedControlList.Clear();

            foreach (Material.MaterialUniformValue unifValue in material.UniformValues)
            {
                UniformEditor unifEditor = UniformTypeFactory.GetEditor(ParentWindow, unifValue);
                unifEditor.OnUniformChanged += (s, a) =>
                    {
                        unifValue.Value = a.NewUniformValue;

                        // Re-Serialize / Save
                        String newJson = JsonConvert.SerializeObject(material, Formatting.Indented);
                        File.WriteAllText(path, newJson);

                        // Force the engine to reload it
                        Material.ForceReload(path);
                    };

                AddIContextComponent(unifEditor);
            }
        }


    }
}
