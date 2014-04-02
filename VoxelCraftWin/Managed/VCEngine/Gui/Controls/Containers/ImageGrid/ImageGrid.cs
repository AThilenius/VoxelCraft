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

        public int TileWidth = 65;
        public int TileHeight = 80;
        public int Padding = 5;

        protected List<ImageGridNode> m_nodes = new List<ImageGridNode>();
        protected int m_filledHeight;

        public ImageGrid(Window window) : base(window)
        {
            Resize += (s, a) => ReBuildGrid();
        }

        public override void AddControl(Control control)
        {
            base.AddControl(control);

            if (!(control is ImageGridNode))
                return;

            m_nodes.Add((ImageGridNode) control);
            ReBuildGrid();
        }

        public override void RemoveControl(Control control)
        {
            base.RemoveControl(control);

            if (!(control is ImageGridNode))
                return;

            m_nodes.Remove((ImageGridNode) control);
            ReBuildGrid();
        }

        public void AnimateOpening()
        {
            // Align all to the upper cent
            foreach (ImageGridNode node in m_nodes)
                node.Frame = new Rectangle( MathHelper.RoundedDevision(Width, 2) - MathHelper.RoundedDevision(TileWidth, 2) , Height - (TileHeight + Padding), TileWidth, TileHeight);

            // Column/Row count must be ( (Width + Padding) / (ImageSize + Padding) )
            int maxColumnCount = (int)((float)(Width + Padding) / (float)(TileWidth + Padding));
            int maxRowCount = (int)((float)(Height + Padding) / (float)(TileHeight + Padding));

            // Begin the animation to there final destination
            int i = 0;
            m_filledHeight = 0;
            for (int row = 0; row < maxRowCount; row++)
            {
                m_filledHeight += TileHeight + Padding;

                for (int col = 0; col < maxColumnCount; col++)
                {
                    if (i >= m_nodes.Count)
                        return;

                    ImageGridNode node = m_nodes[i++];

                    node.Visible = true;
                    node.AnimateLocation(new Point(col * (TileWidth + Padding) + Padding, (Height - (TileHeight + Padding)) - (row * (TileHeight + Padding))));
                }
            }

            // Make any remaining nodes invisible
            for (; i < m_nodes.Count; i++)
                ((ImageGridNode)m_nodes[i]).Visible = false;
        }

        private void ReBuildGrid()
        {
            //// Column/Row count must be ( (Width + Padding) / (ImageSize + Padding) )
            //int maxColumnCount = (int)((float)(Width + Padding) / (float)(TileWidth + Padding));
            //int maxRowCount = (int)((float)(Height + Padding) / (float)(TileHeight + Padding));

            //int i = 0;
            //m_filledHeight = 0;
            //for (int row = 0; row < maxRowCount; row++)
            //{
            //    m_filledHeight += TileHeight + Padding;

            //    for (int col = 0; col < maxColumnCount; col++)
            //    {
            //        if (i >= m_nodes.Count)
            //            return;

            //        ImageGridNode node = m_nodes[i++];

            //        node.Visible = true;
            //        node.Frame = new Rectangle(col * (TileWidth + Padding) + Padding, (Height - (TileHeight + Padding)) - (row * (TileHeight + Padding)), TileWidth, TileHeight);
            //    }
            //}

            //// Make any remaining nodes invisible
            //for (; i < m_nodes.Count; i++)
            //    ((ImageGridNode)m_nodes[i]).Visible = false;

        }

        protected override void Draw()
        {
            Gui.DrawBackground(ScreenFrame);
            //GuiDrawer.DrawBackground(new Rectangle(ScreenFrame.X, ScreenFrame.Y + Height - (m_filledHeight + Padding), Width, m_filledHeight + Padding));
        }

    }
}
