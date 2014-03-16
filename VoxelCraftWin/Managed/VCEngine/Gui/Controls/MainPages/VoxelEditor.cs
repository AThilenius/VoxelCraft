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

        public VoxelEditor()
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
                    RightContextMenu.AnimateLocation(new Point(Editor.MainWindow.ScaledSize.X - 250, 0));
                };
            PanelsTrippleButton.RightButton.OnRelease += (s, a) =>
                {
                    RightContextMenu.AnimateLocation(new Point(Editor.MainWindow.ScaledSize.X, 0));
                };

            // Default page
            base.OnSelected();
        }

        public void Create()
        {
            CreateEditorWindow();
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
            RightContextMenu = new ContextMenu();
            AddControl(RightContextMenu);
            RightContextMenu.Frame = new Rectangle(Width - 250, 0, 250, Height);

            // Tools
            ToolMenu = new Tools();
            RightContextMenu.AddIContextComponent(ToolMenu);

            // HLS
            ColorPicker = new HslColorPicker();
            ColorPicker.Height = 100;
            RightContextMenu.AddIContextComponent(ColorPicker);

            RightContextMenu.ReBuild();
        }

        private void CreateSolutionExplorer()
        {
            SolutionEx = new SolutionExplorer();
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

            EditorWindow.Frame = new Rectangle(0, ScreenFrame.Y, Editor.MainWindow.ScaledSize.X, Editor.MainWindow.ScaledSize.Y - 75);
        }

        private void CreateEditorWindow()
        {
            // HACK
            EditorWindow = new GameWindow(2);
            AddControl(EditorWindow);
            EditorWorld.MasterGameWindow = EditorWindow;
            EditorWindow.Frame = new Rectangle(0, 0, Editor.MainWindow.ScaledSize.X, Editor.MainWindow.ScaledSize.Y - 75);
        }

    }
}