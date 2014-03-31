using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class FilterEditor : MainPageBase
    {
        public static String FiltersDirectory { get { return Path.Combine(PathUtilities.AssetsPath, @"Materials\Filters"); } }

        public TreeView FiltersTreeView;
        public DirectoryObserverTreeNode FileNode;
        public RenderWindow FilterRenderer;

        public FilterEditor(Window window) : base(window)
        {

            // Register panels button callbacks
            PanelsTrippleButton.LeftButton.OnDepressed += (s, a) =>
            {
                FiltersTreeView.AnimateLocation(new Point(0, 0));
                FilterRenderer.AnimateFrame(new Rectangle(250, 0, ParentWindow.ScaledSize.X - 250, ParentWindow.ScaledSize.Y - 75));
            };
            PanelsTrippleButton.LeftButton.OnRelease += (s, a) =>
            {
                FiltersTreeView.AnimateLocation(new Point(-250, 0));
                FilterRenderer.AnimateFrame(new Rectangle(0, 0, ParentWindow.ScaledSize.X, ParentWindow.ScaledSize.Y - 75));
            };

        }

        public void Create()
        {
            CreateTreeView();
            CreateFilterRenderer();
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
            FiltersTreeView = new TreeView(ParentWindow);
            AddControl(FiltersTreeView);
            FiltersTreeView.Frame = new Rectangle(0, 0, 250, ParentWindow.ScaledSize.Y - 75);
            FiltersTreeView.Head.OnItemClicked += (sender, args) =>
            {
                TreeNode node = (TreeNode)sender;

                if (node.UserData == null || !(node.UserData is FileInfo))
                    return;

                // Clear renderable entities, add a new plane with the specified material
                FilterRenderer.GLRenderViewport.Entities.Clear();
                RenderedEntity Plane = new RenderedEntity(@"Models\Plane.obj", @"Materials\Filters\" + ((FileInfo)node.UserData).Name);
                Plane.Transform.Position = new Vector3(-0.5f, -0.5f, -0.75f);
                FilterRenderer.GLRenderViewport.Entities.Add(Plane);
            };

            FileNode = new DirectoryObserverTreeNode(ParentWindow, "Filters", FiltersDirectory, true);
            FiltersTreeView.Head.AddControl(FileNode);
        }

        private void CreateFilterRenderer()
        {
            FilterRenderer = new RenderWindow(ParentWindow);
            AddControl(FilterRenderer);
            FilterRenderer.Frame = new Rectangle(250, 0, ParentWindow.ScaledSize.X - 250, ParentWindow.ScaledSize.Y - 75);
        }

        private void ResizeHandler()
        {
            FiltersTreeView.Size = new Point(250, Height);

            if (PanelsTrippleButton.LeftButton.IsDepressed)
                FilterRenderer.Frame = new Rectangle(250, ScreenFrame.Y, ParentWindow.ScaledSize.X - 250, ParentWindow.ScaledSize.Y - 75);

            else
                FilterRenderer.Frame = new Rectangle(0, ScreenFrame.Y, ParentWindow.ScaledSize.X, ParentWindow.ScaledSize.Y - 75);

        }

    }
}
