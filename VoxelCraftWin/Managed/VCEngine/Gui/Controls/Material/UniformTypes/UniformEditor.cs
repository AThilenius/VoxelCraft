using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class UniformChangeEventArgs : EventArgs
    {
        public String NewUniformValue;

        public UniformChangeEventArgs(String newValue)
        {
            NewUniformValue = newValue;
        }
    }

    /// <summary>
    /// Base class for a Material's Uniform editor
    /// </summary>
    public abstract class UniformEditor : ToolContextComponent
    {

        public abstract event EventHandler<UniformChangeEventArgs> OnUniformChanged;
        public Material.MaterialUniformValue Value;

        public UniformEditor(Window window, Material.MaterialUniformValue value) : base(window, value.Name)
        {
            Value = value;
        }

    }
}
