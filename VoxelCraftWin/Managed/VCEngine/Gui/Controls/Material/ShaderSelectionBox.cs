using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ShaderSelectedEventArgs : EventArgs
    {
        public Shader Shader;

        public ShaderSelectedEventArgs(Shader shader)
        {
            Shader = shader;
        }
    }

    public class ShaderSelectionBox : Control
    {
        public Label ShaderTitle;
        public event EventHandler<ShaderSelectedEventArgs> OnShaderSelected = delegate { };

        private TextField m_shaderNameField;

        public ShaderSelectionBox(Window window) : base(window)
        {
            ShaderTitle = new Label(window, "Shader");
            AddControl(ShaderTitle);

            m_shaderNameField = new TextField(window);
            AddControl(m_shaderNameField);
            m_shaderNameField.Text = "Shader Name";

            m_shaderNameField.TextEntry += (s, a) =>
                {
                    if (Shader.GetByName(m_shaderNameField.Text) != null)
                        m_shaderNameField.FontColor = Color.Black;

                    else
                        m_shaderNameField.FontColor = Color.ControlRed;
                };

            m_shaderNameField.EnterPressed += (s, a) =>
                {
                    Shader shader = Shader.GetByName(m_shaderNameField.Text);

                    // Iff it exists
                    if (shader != null)
                        OnShaderSelected(this, new ShaderSelectedEventArgs(shader));
                };

            Height = 40;
        }

        public void OpenShader(Shader shader)
        {
            m_shaderNameField.Text = shader.Name;
        }

        protected override void Draw()
        {
            base.Draw();

            Gui.DrawButtonAccentuated(new Rectangle(ScreenFrame.X, ScreenFrame.Y + 20, Width, 20));

            ShaderTitle.Frame = new Rectangle(0,20, Width, 20);
            m_shaderNameField.Frame = new Rectangle(0, 0, Width, 20);
        }

    }
}
