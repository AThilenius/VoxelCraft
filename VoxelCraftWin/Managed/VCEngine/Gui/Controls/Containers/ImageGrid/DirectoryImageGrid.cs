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

        public DirectoryImageGrid(String path)
        {
            LoadDirectory(new DirectoryInfo(path));
        }

        private void LoadDirectory(DirectoryInfo directory)
        {
            // Add files in this directory, add callbacks
            foreach (FileInfo fInfo in directory.GetFiles())
            {
                ImageGridNode node = new ImageGridNode(fInfo.Name);

                if (fInfo.Extension == ".DDS")
                    node.Image.ImagePath = fInfo.FullName;

                base.AddControl(node);
            }

        }

    }
}
