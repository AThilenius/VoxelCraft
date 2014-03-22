using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ProjectExplorer : Control
    {
        public String ProjectPath { get; private set; }
        private ProjectHeader m_projHeader;
        private DirectoryExporer m_dirExp;
        private DirectoryContextMenu m_dirContext;

        public ProjectExplorer(Window window, String projName, String path) : base(window)
        {
            ProjectPath = path;

            m_projHeader = new ProjectHeader(ParentWindow, projName, this);
            AddControl(m_projHeader);
            m_projHeader.DockOrder = 0;
            m_projHeader.Dock = Dockings.Top;
            m_projHeader.ExpandButton.OnExpand += (s, a) => m_dirExp.Visible = true;
            m_projHeader.ExpandButton.OnCollapse += (s, a) => m_dirExp.Visible = false;

            m_dirExp = new DirectoryExporer(ParentWindow, path);
            AddControl(m_dirExp);
            m_dirExp.Dock = Dockings.Fill;
            m_dirExp.OnTreeChange += m_dirExp_OnTreeChange;
            m_dirExp_OnTreeChange(m_dirExp, EventArgs.Empty);

            m_dirContext = new DirectoryContextMenu(ParentWindow, m_dirExp);
            window.MainControl.AddControl(m_dirContext);
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

                        tvi.Image = Texture.Get(@"Icons\Cube 256.DDS");
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
