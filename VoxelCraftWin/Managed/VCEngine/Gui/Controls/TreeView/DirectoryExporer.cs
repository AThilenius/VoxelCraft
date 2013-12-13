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
        public event EventHandler OnTreeChange = delegate { };

        private string m_path;

        public DirectoryExporer(String headPath)
        {
            m_path = headPath;
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
            OnTreeChange(this, EventArgs.Empty);
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            Gui.DrawBackground(new Rectangle(sf.X, sf.Y + sf.Height - m_yOffset, sf.Width, m_yOffset), false);

            base.Draw();
        }

        private void LoadDirRecurse(DirectoryInfo directory, TreeViewItem parent)
        {
            // Add directories in this directory
            foreach (DirectoryInfo dInfo in directory.GetDirectories())
            {

                TreeViewItem dirTVI = new TreeViewItem(this, parent);
                dirTVI.BoundObject = dInfo;
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

            // Add files in this directory, add callbacks
            foreach (FileInfo fInfo in directory.GetFiles())
            {
                TreeViewItem fileTVI = new TreeViewItem(this, parent);
                fileTVI.BoundObject = fInfo;
                fileTVI.Text = fInfo.Name;

                if (parent == null)
                    AddItem(fileTVI);

                else
                    parent.AddChildItem(fileTVI);
            }
        }



    }
}
