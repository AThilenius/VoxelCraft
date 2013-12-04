using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class DirectoryExporer : TreeView
    {
        public String HeadPath
        {
            get { return m_path; }
            set
            {
                if (m_path == value)
                    return;

                m_path = value;
                RefreshView();
            }
        }

        private string m_path;

        public DirectoryExporer(String headPath)
        {
            m_path = headPath;
            //GlfwInputState.OnFocusChange += (s, a) =>
            //    {
            //        RefreshView();
            //        m_needsRebuild = true;
            //    };

            RefreshView();
            NotifyUpdate();
        }

        public void RefreshView()
        {
            // Clear Control children too
            Children.Clear();
            m_childrenTVI.Clear();

            if (Directory.Exists(m_path))
                LoadDirRecurse(new DirectoryInfo(m_path), null);

            NotifyUpdate();
        }

        private void LoadDirRecurse(DirectoryInfo directory, TreeViewItem parent)
        {
            // Add directories in this directory
            foreach (DirectoryInfo dInfo in directory.GetDirectories())
            {

                TreeViewItem dirTVI = new TreeViewItem(this, parent);
                dirTVI.Text = dInfo.Name;
                dirTVI.Image = @"Icons\Folder 128.DDS";
                dirTVI.DoubleClick += (s, a) => dirTVI.ExpandCollapse();

                if (parent == null)
                    AddItem(dirTVI);

                else
                    parent.AddChildItem(dirTVI);

                // Depth first
                LoadDirRecurse(dInfo, dirTVI);
            }

            // Add files in this directory
            foreach (FileInfo fInfo in directory.GetFiles())
            {
                TreeViewItem fileTVI = new TreeViewItem(this, parent);
                fileTVI.Text = fInfo.Name;

                if (fInfo.Extension == ".vcm")
                {
                    fileTVI.DoubleClick += (s, a) =>
                    {
                        EditorWorld.MasterGameWindow.World.LoadFromFile(fInfo.FullName);
                        EditorWorld.MasterGameWindow.World.ReBuild();
                    };

                    fileTVI.Image = @"Icons\Cube 256.DDS";
                }

                if (parent == null)
                    AddItem(fileTVI);

                else
                    parent.AddChildItem(fileTVI);
            }
        }

    }
}
