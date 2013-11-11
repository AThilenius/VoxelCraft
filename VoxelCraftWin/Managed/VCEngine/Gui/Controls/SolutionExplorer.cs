using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class SolutionExplorer : VerticalContainer
    {
        
#if DEBUG
        private static string header = @"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\Saves";
#else
        private static string header = Environment.CurrentDirectory + @"\Saves";
#endif

        private Label m_activeLabel;
        private TextField m_activeField;
        private Button m_loadButton;
        private Button m_saveButton;

        public SolutionExplorer()
        {
            m_activeLabel = new Label("File Path: ");
            m_activeField = new TextField();
            m_loadButton = new Button("Load");
            m_saveButton = new Button("Save / Overwrite");

            m_loadButton.Enabled = false;
            m_loadButton.Text = "Load - File Does Not Exist";

            AddControl(m_activeLabel);
            AddControl(m_activeField);
            AddControl(m_loadButton);
            AddControl(m_saveButton);

            m_activeField.TextEntry += m_activeField_TextEntry;
            m_loadButton.Click += m_loadButton_Click;
            m_saveButton.Click += m_saveButton_Click;
        }

        void m_activeField_TextEntry(object sender, CharEventArgs e)
        {
            if (File.Exists(Path.Combine(header, m_activeField.Text)))
            {
                m_loadButton.Enabled = true;
                m_loadButton.Text = "Load";
            }

            else
            {
                m_loadButton.Enabled = false;
                m_loadButton.Text = "Load - File Does Not Exist";
            }
        }

        void m_loadButton_Click(object sender, MouseEventArgs e)
        {
            string filePath = Path.Combine(header, m_activeField.Text);

            EditorWorld.MasterGameWindow.World.LoadFromFile(filePath);
            EditorWorld.MasterGameWindow.World.ReBuild();
        }


        void m_saveButton_Click(object sender, MouseEventArgs e)
        {
            string filePath = Path.Combine(header, m_activeField.Text);

            if (!Directory.Exists(header))
                Directory.CreateDirectory(header);

            if (!File.Exists(filePath))
                File.Create(filePath).Dispose();

            EditorWorld.MasterGameWindow.World.SaveToFile(filePath);
            m_activeField_TextEntry(this, null);
        }

    }
}
