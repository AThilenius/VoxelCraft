using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialEditorRGBA : UniformEditor
    {

        public override event EventHandler<UniformChangeEventArgs> OnUniformChanged = delegate { };
        public HslColorPicker ColorPicker;

        public MaterialEditorRGBA(Window window, Material.MaterialUniformValue value) : base(window, value)
        {
            ColorPicker = new HslColorPicker(window);
            AddControl(ColorPicker);
            ColorPicker.Dock = Dockings.Fill;
            ColorPicker.ColorRGB = Color.ParseJson(value.Value);
            ColorPicker.OnColorChange += (s, a) => OnUniformChanged(s, new UniformChangeEventArgs(ColorPicker.ColorRGB.ToJsonString()));

            Height = 100;
        }
    }
}
