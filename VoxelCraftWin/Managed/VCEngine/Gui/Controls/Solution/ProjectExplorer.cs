using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ProjectExplorer : Control
    {

        private ProjectHeader m_projHeader;
        private DirectoryExporer m_dirExp;
        private DirectoryContextMenu m_dirContext;

        public ProjectExplorer(String projName, String path)
        {
            m_dirExp = new DirectoryExporer(path);
            AddControl(m_dirExp);
            m_dirExp.DockOrder = 1;
            m_dirExp.Dock = Dockings.Fill;
            m_dirExp.OnTreeChange += m_dirExp_OnTreeChange;
            m_dirExp_OnTreeChange(m_dirExp, EventArgs.Empty);

            m_dirContext = new DirectoryContextMenu(m_dirExp);
            Control.MainControl.AddControl(m_dirContext);

            m_projHeader = new ProjectHeader(projName);
            AddControl(m_projHeader);
            m_projHeader.Dock = Dockings.Top;
            m_projHeader.ExpandButton.OnExpand += (s, a) => m_dirExp.Visible = true;
            m_projHeader.ExpandButton.OnCollapse += (s, a) => m_dirExp.Visible = false;
        }

        private void m_dirExp_OnTreeChange(object sender, EventArgs e)
        {
            foreach (TreeViewItem tvi in m_dirExp.AllItems)
            {
                if (tvi.BoundObject is FileInfo)
                {
                    FileInfo fInfo = (FileInfo)tvi.BoundObject;

                    if (fInfo.Extension == ".vcm")
                    {
                        tvi.DoubleClick += (s, a) =>
                        {
                            EditorWorld.MasterGameWindow.World.LoadFromFile(fInfo.FullName);
                            EditorWorld.MasterGameWindow.World.ReBuild();
                        };

                        tvi.Image = @"Icons\Cube 256.DDS";
                    }
                }

                if (tvi.BoundObject is DirectoryInfo)
                {
                    tvi.RightClick += (s, a) => m_dirContext.Display((DirectoryInfo) tvi.BoundObject);
                }

                
            }
        }

    }
}
