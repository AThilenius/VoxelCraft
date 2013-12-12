using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class SolutionExplorer : Control
    {
        // Right now only supports one project
        private ProjectExplorer m_project;
        
        public void AddProject(String name, String path)
        {
            m_project = new ProjectExplorer(name, path);
            AddControl(m_project);
            m_project.Dock = Dockings.Fill;
            m_project.Frame = m_project.Frame;
        }

        protected override void Draw()
        {
            Gui.DrawBackgroundEmpty(ScreenFrame, false);
        }

    }
}
