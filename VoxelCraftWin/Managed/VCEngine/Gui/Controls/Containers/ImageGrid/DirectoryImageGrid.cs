using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// An extension of the Image grid used to watch a system directory.
    /// </summary>
    public class DirectoryImageGrid : ImageGrid
    {
        public String Path
        {
            get { return m_path; }
            set
            {
                m_path = value;
                LoadDirectory(new DirectoryInfo(value));
            }
        }

        private String m_path = "";

        public DirectoryImageGrid(Window window) : base(window)
        {
        }

        private void LoadDirectory(DirectoryInfo directory)
        {
            base.m_nodes.ForEach(node => base.Children.Remove(node));
            base.m_nodes.Clear();

            // Add files in this directory, add callbacks
            foreach (FileInfo fInfo in directory.GetFiles())
            {
                ImageGridNode node = new ImageGridNode(ParentWindow, fInfo.Name);

                if (fInfo.Extension == ".DDS")
                    node.Image.ImagePath = fInfo.FullName;

                base.AddControl(node);
            }

        }

    }
}
