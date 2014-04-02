using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ModelEditor : MainPageBase
    {
        public static String ModelsDirectory { get { return Path.Combine(PathUtilities.AssetsPath, "Models"); } }

        // Left Pane
        public TreeView FoldersTreeView;
        public DirectoryObserverTreeNode DirectoryNode;

        // Central Pane
        public MaterialPreviewer MaterialPreivew;

        // Center - Lower Pane
        public DirectoryImageGrid TileViewer;

        // Right Pane
        public MaterialPropertiesPane MaterialProperties;

        protected override Control LeftPane { get { return FoldersTreeView; } }
        protected override Control RightPane { get { return MaterialProperties; } }
        protected override Control CenterPane { get { return MaterialPreivew; } }
        protected override Control LowerPane { get { return TileViewer; } }


        public ModelEditor(Window window) : base(window)
        {

            // Register panels button callbacks
            PanelsTrippleButton.LeftButton.OnDepressed += (s, a) =>
            {
                FoldersTreeView.AnimateLocation(new Point(0, 0));
                //TileViewer.AnimateFrame(new Rectangle(250, 0, ParentWindow.ScaledSize.X - 250, ParentWindow.ScaledSize.Y - 75));
            };
            PanelsTrippleButton.LeftButton.OnRelease += (s, a) =>
            {
                FoldersTreeView.AnimateLocation(new Point(-250, 0));
                //TileViewer.AnimateFrame(new Rectangle(0, 0, ParentWindow.ScaledSize.X, ParentWindow.ScaledSize.Y - 75));
            };

        }

        public void Create()
        {
            CreateTreeView();
            CreateTileViewer();
            CreateMaterialPreview();
            CreateMaterialProperties();

            ResizeHandler();
            Resize += (s, a) =>
            {
                if (a.From != a.To)
                    ResizeHandler();
            };
        }


        private void CreateTreeView()
        {
            // Directory Tree view
            FoldersTreeView = new TreeView(ParentWindow);
            AddControl(FoldersTreeView);
            FoldersTreeView.Frame = new Rectangle(0, 0, 250, ParentWindow.ScaledSize.Y - 75);
            FoldersTreeView.Head.OnItemClicked += (sender, args) =>
            {
                TreeNode node = (TreeNode)sender;

                if (node.UserData == null || !(node.UserData is FileInfo))
                    return;

                String path = ((FileInfo)node.UserData).FullName;
                MaterialPreivew.OpenMaterialPath(path);
                MaterialProperties.OpenMaterial(path);
            };

            DirectoryNode = new DirectoryObserverTreeNode(ParentWindow, "Materials", ModelsDirectory, true);
            FoldersTreeView.Head.AddControl(DirectoryNode);
        }

        private void CreateTileViewer()
        {
            TileViewer = new DirectoryImageGrid(ParentWindow);
            AddControl(TileViewer);
            TileViewer.Frame = new Rectangle(250, 0, ParentWindow.ScaledSize.X - 500, 300);

            TileViewer.Path = Path.Combine(PathUtilities.AssetsPath, @"Textures");
        }

        private void CreateMaterialPreview()
        {
            MaterialPreivew = new MaterialPreviewer(ParentWindow);
            AddControl(MaterialPreivew);
            MaterialPreivew.Frame = new Rectangle(250, 300, ParentWindow.ScaledSize.X - 500, ParentWindow.ScaledSize.Y - (300 + 75));
        }

        private void CreateMaterialProperties()
        {
            MaterialProperties = new MaterialPropertiesPane(ParentWindow);
            AddControl(MaterialProperties);
            MaterialProperties.Frame = new Rectangle(ParentWindow.ScaledSize.X - 250, 0, 250, ParentWindow.ScaledSize.Y - 75);
        }

        private void ResizeHandler()
        {
            FoldersTreeView.Size = new Point(250, Height);

            //if ( PanelsTrippleButton.LeftButton.IsDepressed )
            //    TileViewer.Frame = new Rectangle(250, ScreenFrame.Y, ParentWindow.ScaledSize.X - 250, ParentWindow.ScaledSize.Y - 75);

            //else
            //    TileViewer.Frame = new Rectangle(0, ScreenFrame.Y, ParentWindow.ScaledSize.X, ParentWindow.ScaledSize.Y - 75);

            //TileViewer.AnimateOpening();
        }

    }
}
