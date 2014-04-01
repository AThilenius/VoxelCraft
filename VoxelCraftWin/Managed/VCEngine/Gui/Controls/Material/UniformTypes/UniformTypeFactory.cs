using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// A Gazillion better C# ways to do this but I'm lazy right now
    /// </summary>
    public class UniformTypeFactory
    {
        public static UniformEditor GetEditor(Window window, Material.MaterialUniformValue uniformValue)
        {
            switch (uniformValue.Type)
            {
                case ShaderUniform.ValueTypes.Float:        return new MaterialEditorUnknown    (window, uniformValue);
                case ShaderUniform.ValueTypes.Int:          return new MaterialEditorUnknown    (window, uniformValue);
                case ShaderUniform.ValueTypes.Vector2:      return new MaterialEditorUnknown    (window, uniformValue);
                case ShaderUniform.ValueTypes.Vector3:      return new MaterialEditorUnknown    (window, uniformValue);
                case ShaderUniform.ValueTypes.Vector4:      return new MaterialEditorUnknown    (window, uniformValue);
                case ShaderUniform.ValueTypes.Matrix3:      return new MaterialEditorUnknown    (window, uniformValue);
                case ShaderUniform.ValueTypes.Matrix4:      return new MaterialEditorUnknown    (window, uniformValue);
                case ShaderUniform.ValueTypes.ColorRGBA:    return new MaterialEditorRGBA       (window, uniformValue);
                case ShaderUniform.ValueTypes.Sampler2D:    return new MaterialEditorSampler2D  (window, uniformValue);
                case ShaderUniform.ValueTypes.Sampler3D:    return new MaterialEditorUnknown    (window, uniformValue);
                default:                                    return new MaterialEditorUnknown    (window, uniformValue);
            }
        }
    }
}
