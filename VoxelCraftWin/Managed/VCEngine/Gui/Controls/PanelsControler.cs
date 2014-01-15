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

        private ValueAnimator<Point> m_rightAnimator;

        public PanelsControler()
        {
            m_rightAnimator = new ValueAnimator<Point>(new Point(EditorGui.VoxelEditor.Width - 250, 0));

            m_left = new ToggleButton(" ");
            m_left.ImagePath = @"Icons\LeftPane.DDS";
            m_left.Width = 30;
            m_left.Style = ToggleButton.ToggleStyle.TriLeft;
            m_left.IsDepressed = true;
            m_left.OnRelease += (s, a) => EditorGui.VoxelEditor.SolutionEx.AnimateLocation(new Point(-250, 0));
            m_left.OnDepressed += (s, a) => EditorGui.VoxelEditor.SolutionEx.AnimateLocation(new Point(0, 0));
            AddControl(m_left);

            m_right = new ToggleButton(" ");
            m_right.Width = 30;
            m_right.ImagePath = @"Icons\RightPane.DDS";
            m_right.Style = ToggleButton.ToggleStyle.TriRight;
            m_right.IsDepressed = true;
            m_right.OnRelease += (s, a) => EditorGui.VoxelEditor.RightContextMenu.AnimateLocation(new Point(EditorGui.VoxelEditor.Width, 0));
            m_right.OnDepressed += (s, a) => EditorGui.VoxelEditor.RightContextMenu.AnimateLocation(new Point(EditorGui.VoxelEditor.Width - 250, 0));
            AddControl(m_right);

            // Manual Resize Handlers
            Window.Resize += (s, a) =>
                {
                    EditorGui.VoxelEditor.SolutionEx.Frame = new Rectangle(0, 0, 250, EditorGui.VoxelEditor.SolutionEx.Height);
                    EditorGui.VoxelEditor.RightContextMenu.Frame = new Rectangle(EditorGui.VoxelEditor.Width - 250, 0, 250, EditorGui.VoxelEditor.SolutionEx.Height);
                };

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
