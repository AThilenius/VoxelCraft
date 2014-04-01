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

        public SolutionExplorer(Window window) : base(window)
        {

        }

        public void AddProject(String name, String path)
        {
            m_project = new ProjectExplorer(ParentWindow, name, path);
            AddControl(m_project);
            m_project.Dock = Dockings.Fill;
        }

        protected override void Draw()
        {
            Gui.DrawBackgroundEmpty(ScreenFrame, false);
        }

    }
}
