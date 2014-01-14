using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class VoxelEditor : Control
    {
        public HslColorPicker ColorPicker;
        public GameWindow EditorWindow;
        public ContextMenu RightContextMenu;
        public SolutionExplorer SolutionEx;
        public Tools ToolMenu;

        public void Create()
        {
            FillColorControls();
            CreateSolutionExplorer();
            CreateEditorWindow();

            Window.Resize += (s, a) => Size = new Point(a.To.Width, a.To.Height);
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
        }

        private void CreateSolutionExplorer()
        {
            SolutionEx = new SolutionExplorer();
            AddControl(SolutionEx);
            SolutionEx.AddProject("Voxel Game", PathUtilities.AssetsPath);
            SolutionEx.Frame = new Rectangle(0, 0, 250, Height);
        }

        private void CreateEditorWindow()
        {
            // HACK
            //EditorWindow = new GameWindow(2);
            //Control.MainControl.AddControl(EditorWindow);
            //EditorWorld.MasterGameWindow = EditorWindow;
            //EditorWindow.DockOrder = 2;
            ////EditorWindow.Dock = Control.Dockings.Fill;
            //EditorWindow.Frame = EditorWindow.Frame;
        }

    }
}
