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
        public MaterialPropertiesPane MaterialProperties;

        public override string Name { get { return "Material"; } }
        protected override Control LeftPane { get { return FoldersTreeView; } }
        protected override Control RightPane { get { return MaterialProperties; } }
        protected override Control CenterPane { get { return MaterialPreivew; } }
        protected override Control LowerPane { get { return TileViewer; } }

        public MaterialEditor(Window window) : base(window)
        {
        }

        public void Create()
        {
            CreateTreeView();
            CreateTileViewer();
            CreateMaterialPreview();
            CreateMaterialProperties();
            ResizeHandler();
        }

        private void CreateTreeView()
        {
            // Directory Tree view
            FoldersTreeView = new TreeView(ParentWindow);
            AddControl(FoldersTreeView);
            FoldersTreeView.Head.OnItemClicked += (sender, args) =>
            {
                TreeNode node = (TreeNode)sender;

                if (node.UserData == null || !(node.UserData is FileInfo))
                    return;

                String path = ((FileInfo)node.UserData).FullName;
                MaterialPreivew.OpenMaterialPath(path);
                MaterialProperties.OpenMaterial(path);
            };

            DirectoryNode = new DirectoryObserverTreeNode(ParentWindow, "Materials", MaterialsDirectory, true);
            FoldersTreeView.Head.AddControl(DirectoryNode);
        }

        private void CreateTileViewer()
        {
            TileViewer = new DirectoryImageGrid(ParentWindow);
            AddControl(TileViewer);

            TileViewer.Path = Path.Combine(PathUtilities.AssetsPath, @"Textures");
        }

        private void CreateMaterialPreview()
        {
            MaterialPreivew = new MaterialPreviewer(ParentWindow);
            AddControl(MaterialPreivew);
        }

        private void CreateMaterialProperties()
        {
            MaterialProperties = new MaterialPropertiesPane(ParentWindow);
            AddControl(MaterialProperties);
        }

    }
}
