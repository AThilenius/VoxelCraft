using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialEditorUnknown : UniformEditor
    {
        public override event EventHandler<UniformChangeEventArgs> OnUniformChanged = delegate { };
        public TextField ValueTextField;

        public MaterialEditorUnknown(Window window, Material.MaterialUniformValue value) : base(window, value)
        {
            ValueTextField = new TextField(window);
            AddControl(ValueTextField);
            ValueTextField.Dock = Dockings.Fill;
            ValueTextField.Text = value.Value;

            ValueTextField.EnterPressed += (s, a) => OnUniformChanged(s, new UniformChangeEventArgs(ValueTextField.Text));

            Height = 30;
        }

    }
}
