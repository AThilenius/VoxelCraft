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

        public MaterialEditor()
        {
            // Directory view
            FoldersTreeView = new TreeView();
            AddControl(FoldersTreeView);
            FoldersTreeView.Frame = new Rectangle(0, 0, 250, Window.ScaledSize.Y - 75);
            FoldersTreeView.Head.OnItemClicked += (sender, args) =>
                {
                    TreeNode node = (TreeNode) sender;

                    if (node.UserData == null || !(node.UserData is DirectoryInfo))
                        return;

                    TileViewer.Path = ((DirectoryInfo)node.UserData).FullName;
                };

            DirectoryNode = new DirectoryObserverTreeNode("Packages", TexturesDirectory, false);
            FoldersTreeView.Head.AddControl(DirectoryNode);

            TileViewer = new DirectoryImageGrid();
            AddControl(TileViewer);
            TileViewer.Frame = new Rectangle(250, 0, Window.ScaledSize.X - 250, Window.ScaledSize.Y - 75);
        }

        protected override void Draw()
        {
            Gui.DrawBorderedRect(ScreenFrame, Color.ControlDark, Color.ControlRed, 5);
        }
    }
}
