using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialPropertiesPane : Control
    {
        public ShaderSelectionBox ShaderSelectField;
        public MaterialPropertiesContextMenu MaterialContextMenu;

        public MaterialPropertiesPane(Window window) : base(window)
        {
            ShaderSelectField = new ShaderSelectionBox(window);
            AddControl(ShaderSelectField);

            MaterialContextMenu = new MaterialPropertiesContextMenu(window);
            AddControl(MaterialContextMenu);

            Resize += (s, a) => ResizeHandler();

            // When the user changes shader types, reload the Material properties
            ShaderSelectField.OnShaderSelected += (s, a) => MaterialContextMenu.ChangeShaderType(a.Shader);
        }

        public void OpenMaterial(String path)
        {
            Material mat = JsonConvert.DeserializeObject<Material>(File.ReadAllText(path));
            Shader shader = Shader.GetByName(mat.Shader);

            ShaderSelectField.OpenShader(shader);
            MaterialContextMenu.OpenMaterial(mat, path);
        }

        private void ResizeHandler()
        {
            ShaderSelectField.Frame = new Rectangle(0, Height - ShaderSelectField.Height, Width, ShaderSelectField.Height);
            MaterialContextMenu.Frame = new Rectangle(0, 0, Width, Height - ShaderSelectField.Height);
        }

    }
}
