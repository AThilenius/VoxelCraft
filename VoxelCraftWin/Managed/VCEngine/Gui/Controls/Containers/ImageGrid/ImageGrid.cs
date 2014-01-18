using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// Hosts a 2D grid of images (Ex. Image file explorer)
    /// </summary>
    public class ImageGrid : Control
    {

        public int TileWidth = 100;
        public int TileHeight = 110;
        public int Padding = 10;

        private List<ImageGridNode> m_nodes = new List<ImageGridNode>();

        public ImageGrid()
        {
            Resize += (s, a) => ReBuildGrid();
        }

        public override void AddControl(Control control)
        {
            base.AddControl(control);

            if (!(control is ImageGridNode))
                return;

            m_nodes.Add((ImageGridNode) control);
            //ReBuildGrid();
        }

        public override void RemoveControl(Control control)
        {
            base.RemoveControl(control);

            if (!(control is ImageGridNode))
                return;

            m_nodes.Remove((ImageGridNode) control);
            ReBuildGrid();
        }

        private void ReBuildGrid()
        {
            // Column/Row count must be ( (Width + Padding) / (ImageSize + Padding) )
            int maxColumnCount = (int)((float)(Width + Padding) / (float)(TileWidth + Padding));
            int maxRowCount = (int)((float)(Height + Padding) / (float)(TileHeight + Padding));

            int i = 0;
            for (int row = 0; row < maxRowCount; row++)
            {
                for (int col = 0; col < maxColumnCount; col++)
                {
                    if (i >= m_nodes.Count)
                        return;

                    ImageGridNode node = m_nodes[i++];

                    if (node.Visible == false)
                        continue;

                    node.Frame = new Rectangle(col * (TileWidth + Padding) + Padding, (Height - (TileHeight + Padding)) - (row * (TileHeight + Padding)), TileWidth, TileHeight);
                }
            }


        }

    }
}
