using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialEditor : MainPageBase
    {
        public static String TexturesDirectory { get { return Path.Combine(PathUtilities.AssetsPath, "Textures"); } }

        public TreeView FoldersTreeView;
        public DirectoryObserverTreeNode DirectoryNode;
        public DirectoryImageGrid TileViewer;

        public MaterialEditor(Window window) : base(window)
        {
            // Directory view
            FoldersTreeView = new TreeView(ParentWindow);
            AddControl(FoldersTreeView);
            FoldersTreeView.Frame = new Rectangle(0, 0, 250, ParentWindow.ScaledSize.Y - 75);
            FoldersTreeView.Head.OnItemClicked += (sender, args) =>
                {
                    TreeNode node = (TreeNode) sender;

                    if (node.UserData == null || !(node.UserData is DirectoryInfo))
                        return;

                    TileViewer.Path = ((DirectoryInfo)node.UserData).FullName;
                };

            DirectoryNode = new DirectoryObserverTreeNode(ParentWindow, "Packages", TexturesDirectory, false);
            FoldersTreeView.Head.AddControl(DirectoryNode);

            TileViewer = new DirectoryImageGrid(ParentWindow);
            AddControl(TileViewer);
            TileViewer.Frame = new Rectangle(250, 0, ParentWindow.ScaledSize.X - 250, ParentWindow.ScaledSize.Y - 75);

            Resize += (s, a) => ResizeHandler();
            ResizeHandler();

            // Panels Handlers
            PanelsTrippleButton.LeftButton.OnDepressed += (s, a) =>
                {
                    FoldersTreeView.AnimateLocation(new Point(0, 0));
                    //TileViewer.AnimateFrame(new Rectangle(250, 0, Width - 250, Height));
                };
            PanelsTrippleButton.LeftButton.OnRelease += (s, a) =>
                {
                    FoldersTreeView.AnimateLocation(new Point(-250, 0));
                    //TileViewer.AnimateFrame(new Rectangle(0, 0, Width, Height));
                };
        }

        protected override void Draw()
        {
            GuiDrawer.DrawBorderedRect(ScreenFrame, Color.ControlDark, Color.ControlRed, 5);
        }

        private void ResizeHandler()
        {
            //FoldersTreeView.Size = new Point(250, Height);

            //if (PanelsTrippleButton.LeftButton.IsDepressed)
            //    TileViewer.Frame = new Rectangle(250, 0, Width - 250, Height);

            //else
            //    TileViewer.Frame = new Rectangle(0, 0, Width, Height);
        }

    }
}
