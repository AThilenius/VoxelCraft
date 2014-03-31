using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class VoxelEditor : MainPageBase
    {
        public HslColorPicker ColorPicker;
        public GameWindow EditorWindow;
        public Tools ToolMenu;

        public ContextMenu RightContextMenu;
        public SolutionExplorer SolutionEx;

        public VoxelEditor(Window window) : base(window)
        {
            // Register panels button callbacks
            PanelsTrippleButton.LeftButton.OnDepressed += (s, a) =>
                {
                    SolutionEx.AnimateLocation(new Point(0, 0));
                };
            PanelsTrippleButton.LeftButton.OnRelease += (s, a) => 
                {
                    SolutionEx.AnimateLocation(new Point(-250, 0));
                };
            PanelsTrippleButton.RightButton.OnDepressed += (s, a) => 
                {
                    RightContextMenu.AnimateLocation(new Point(ParentWindow.ScaledSize.X - 250, 0));
                };
            PanelsTrippleButton.RightButton.OnRelease += (s, a) =>
                {
                    RightContextMenu.AnimateLocation(new Point(ParentWindow.ScaledSize.X, 0));
                };

            // Default page
            base.OnSelected();
        }

        public void Create()
        {
            //CreateEditorWindow();
            FillColorControls();
            CreateSolutionExplorer();
            ResizeHandler();
            Resize += (s, a) =>
                {
                    if (a.From != a.To)
                        ResizeHandler();
                };
        }

        private void FillColorControls()
        {
            RightContextMenu = new ContextMenu(ParentWindow);
            AddControl(RightContextMenu);
            RightContextMenu.Frame = new Rectangle(Width - 250, 0, 250, Height);

            // Tools
            ToolMenu = new Tools(ParentWindow, EditorWindow);
            RightContextMenu.AddIContextComponent(ToolMenu);

            // HLS
            ColorPicker = new HslColorPicker(ParentWindow);
            ColorPicker.Height = 100;
            RightContextMenu.AddIContextComponent(ColorPicker);

            RightContextMenu.ReBuild();
        }

        private void CreateSolutionExplorer()
        {
            SolutionEx = new SolutionExplorer(ParentWindow);
            AddControl(SolutionEx);
            SolutionEx.AddProject("Voxel Game", PathUtilities.AssetsPath);
        }

        private void ResizeHandler()
        {
            SolutionEx.Size = new Point(250, Height);
            RightContextMenu.Size = new Point(250, Height);

            if (PanelsTrippleButton.RightButton.IsDepressed)
                RightContextMenu.Location = new Point(Width - 250, 0);

            else
                RightContextMenu.Location = new Point(Width, 0);

            //EditorWindow.Frame = new Rectangle(0, ScreenFrame.Y, ParentWindow.ScaledSize.X, ParentWindow.ScaledSize.Y - 75);
        }

        private void CreateEditorWindow()
        {
            // HACK
            EditorWindow = new GameWindow(ParentWindow, 2);
            AddControl(EditorWindow);
            EditorWorld.MasterGameWindow = EditorWindow;
            EditorWindow.Frame = new Rectangle(0, 0, ParentWindow.ScaledSize.X, ParentWindow.ScaledSize.Y - 75);
        }

    }
}