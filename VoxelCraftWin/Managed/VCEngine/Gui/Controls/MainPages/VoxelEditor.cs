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

        public override string Name { get { return "Voxel"; } }
        protected override Control LeftPane { get { return SolutionEx; } }
        protected override Control RightPane { get { return RightContextMenu; } }
        protected override Control CenterPane { get { return EditorWindow; } }
        protected override Control LowerPane { get { return null; } }

        public VoxelEditor(Window window) : base(window)
        {
        }

        public void Create()
        {
            CreateEditorWindow();
            FillColorControls();
            CreateSolutionExplorer();
            ResizeHandler();
        }

        private void FillColorControls()
        {
            RightContextMenu = new ContextMenu(ParentWindow);
            AddControl(RightContextMenu);

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

        private void CreateEditorWindow()
        {
            // HACK
            EditorWindow = new GameWindow(ParentWindow, 2);
            AddControl(EditorWindow);
            EditorWorld.MasterGameWindow = EditorWindow;
        }

    }
}