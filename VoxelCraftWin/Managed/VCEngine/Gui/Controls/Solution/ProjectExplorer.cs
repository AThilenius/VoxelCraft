using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ProjectExplorer : Control
    {

        private ProjectHeader m_projHeader;
        private DirectoryExporer m_dirExp;

        public ProjectExplorer(String projName, String path)
        {
            m_dirExp = new DirectoryExporer(path);
            AddControl(m_dirExp);
            m_dirExp.DockOrder = 1;
            m_dirExp.Dock = Dockings.Fill;

            m_projHeader = new ProjectHeader(projName);
            AddControl(m_projHeader);
            m_projHeader.Dock = Dockings.Top;
            m_projHeader.ExpandButton.OnExpand += (s, a) => m_dirExp.Visible = true;
            m_projHeader.ExpandButton.OnCollapse += (s, a) => m_dirExp.Visible = false;
        }

    }
}
