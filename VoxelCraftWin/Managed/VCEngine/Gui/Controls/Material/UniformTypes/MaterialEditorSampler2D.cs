using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialEditorSampler2D : UniformEditor
    {

        public override event EventHandler<UniformChangeEventArgs> OnUniformChanged = delegate { };
        public ImageView Image;

        public MaterialEditorSampler2D(Window window, Material.MaterialUniformValue value) : base(window, value)
        {
            Image = new ImageView(window);
            AddControl(Image);
            Image.Dock = Dockings.Fill;
            Image.Image = Texture.GetInAssets(value.Value);

            // Accept a Texture object as a drag drop
            DragDrop += (s, a) =>
                {
                    if (!(a.Message is Texture))
                        return;

                    Texture tex = (Texture)a.Message;
                    
                    Image.Image = tex;
                    OnUniformChanged(this, new UniformChangeEventArgs(PathUtilities.RelativePath(tex.Fullpath)));
                };

            Height = 200;
        }
    }
}
