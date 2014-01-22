using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MainPagesPicker : Control
    {
        private ToggleButton m_voxelButton;
        private ToggleButton m_materialButton;
        private MainPageBase m_lastSelected;

        public MainPagesPicker()
        {
            m_voxelButton = new ToggleButton("Voxel");
            m_voxelButton.Style = ToggleButton.ToggleStyle.TriLeft;
            m_voxelButton.OnDepressed += (s, a) =>
                {
                    EditorGui.MainSpinner.Select(EditorGui.VoxelEditor);

                    if (m_lastSelected != null)
                        m_lastSelected.OnDeselected();

                    EditorGui.VoxelEditor.OnSelected();
                };
            AddControl(m_voxelButton);

            m_materialButton = new ToggleButton("Materials");
            m_materialButton.Style = ToggleButton.ToggleStyle.TriRight;
            m_materialButton.OnDepressed += (s, a) =>
                {
                    EditorGui.MainSpinner.Select(EditorGui.MaterialEditor);

                    if (m_lastSelected != null)
                        m_lastSelected.OnDeselected();

                    EditorGui.MaterialEditor.OnSelected();
                };
            AddControl(m_materialButton);

            ToggleButton.CreateGroup(m_voxelButton, m_materialButton);
            m_voxelButton.Activate();
            
            Height = m_voxelButton.Height;
            Width = m_voxelButton.Width + m_materialButton.Width;
        }

        protected override void Draw()
        {
            int width = MathHelper.RoundedDevision(Frame.Width, 2);

            m_voxelButton.Frame = new Rectangle(0, 0, m_voxelButton.Width, m_voxelButton.Height);
            m_materialButton.Frame = new Rectangle(m_voxelButton.Width - 2, 0, m_materialButton.Width, m_materialButton.Height);
        }

    }
}
