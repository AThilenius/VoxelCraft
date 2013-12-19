using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class PanelsControler : Control
    {
        private ToggleButton m_left;
        private ToggleButton m_right;

        public PanelsControler()
        {
            m_left = new ToggleButton("Left");
            m_left.Style = ToggleButton.ToggleStyle.TriLeft;
            m_left.IsDepressed = true;
            m_left.OnRelease += (s, a) =>
            {
                EditorGui.SolutionEx.Visible = false;
                Control.RefreshDocks();
            };
            m_left.OnDepressed += (s, a) =>
            {
                EditorGui.SolutionEx.Visible = true;
                Control.RefreshDocks();
            };
            AddControl(m_left);

            m_right = new ToggleButton("Right");
            m_right.Style = ToggleButton.ToggleStyle.TriRight;
            m_right.IsDepressed = true;
            m_right.OnRelease += (s, a) =>
            {
                EditorGui.RightContextMenu.Visible = false;
                Control.RefreshDocks();
            };
            m_right.OnDepressed += (s, a) =>
            {
                EditorGui.RightContextMenu.Visible = true;
                Control.RefreshDocks();
            };
            AddControl(m_right);


            m_left.Width = m_right.Width;

            Height = m_left.Height;
            Width = m_left.Width + m_right.Width;
        }

        protected override void Draw()
        {
            int width = MathHelper.RoundedDevision(Frame.Width, 2);

            m_left.Frame = new Rectangle(width * 0, 0, width, m_left.Height);
            m_right.Frame = new Rectangle(width * 1 - 2, 0, width, m_right.Height);
        }

    }
}
