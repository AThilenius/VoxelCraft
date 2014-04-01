using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialEditor : MainPageBase
    {
        public static String MaterialsDirectory { get { return Path.Combine(PathUtilities.AssetsPath, "Materials"); } }

        // Left Pane
        public TreeView FoldersTreeView;
        public DirectoryObserverTreeNode DirectoryNode;

        // Central Pane
        public MaterialPreviewer MaterialPreivew;

        // Center - Lower Pane
        public DirectoryImageGrid TileViewer;

        // Right Pane
        public MaterialPropertiesContextMenu MaterialProperties;

        public MaterialEditor(Window window) : base(window)
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

        protected override void Draw()
        {
            GuiDrawer.DrawBorderedRect(ScreenFrame, Color.ControlDark, Color.ControlRed, 5);
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
                MaterialProperties.SetMaterial(JsonConvert.DeserializeObject<Material>(File.ReadAllText(path)), path);
                MaterialPreivew.MaterialPath = ((FileInfo)node.UserData).FullName;
            };

            DirectoryNode = new DirectoryObserverTreeNode(ParentWindow, "Materials", MaterialsDirectory, true);
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
            MaterialProperties = new MaterialPropertiesContextMenu(ParentWindow);
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
