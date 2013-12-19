using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorGui
    {
        public static Header HeaderBar;
        public static HslColorPicker ColorPicker;
        public static GameWindow EditorWindow;
        public static ContextMenu RightContextMenu;
        public static SolutionExplorer SolutionEx;
        public static Tools ToolMenu;

        public static void Initialize()
        {
            // Main Control
            Control.MainControl = new Control();
            Control.MainControl.ScreenFrame = new Rectangle(0, 0, Window.ScaledSize);
            Control.MainControl.SetFirstResponder();

            CreateMenuBar();
            FillColorControls();
            CreateSolutionExplorer();
            CreateEditorWindow();
            Control.MainControl.Frame = Control.MainControl.Frame;
        }

        private static void CreateMenuBar()
        {
            HeaderBar = new Header();
            HeaderBar.Layer = 10;
            Control.MainControl.AddControl(HeaderBar);
            HeaderBar.DockOrder = 0;
            HeaderBar.Dock = Control.Dockings.Top;
            HeaderBar.Frame = new Rectangle(0, 0, 0, 75);
        }

        private static void FillColorControls()
        {
            RightContextMenu = new ContextMenu();
            Control.MainControl.AddControl(RightContextMenu);

            RightContextMenu.DockOrder = 1;
            //RightContextMenu.Dock = Control.Dockings.Right;
            RightContextMenu.Frame = new Rectangle(Window.ScaledSize.X - 250, 0, 250, Window.ScaledSize.Y - 75);

            // Tools
            ToolMenu = new Tools();
            RightContextMenu.AddControl(ToolMenu);

            // HLS
            ColorPicker = new HslColorPicker();
            ColorPicker.Height = 100;
            RightContextMenu.AddControl(ColorPicker);
        }

        private static void CreateSolutionExplorer()
        {
            SolutionEx = new SolutionExplorer();
            Control.MainControl.AddControl(SolutionEx);
            SolutionEx.DockOrder = 2;
            //SolutionEx.Dock = Control.Dockings.Left;
            SolutionEx.AddProject("Love Monkey Game", PathUtilities.AssetsPath);
            SolutionEx.Frame = new Rectangle(0, 0, 250, Window.ScaledSize.Y - 75);
        }

        private static void CreateEditorWindow()
        {
            // HACK
            EditorWindow = new GameWindow(2);
            Control.MainControl.AddControl(EditorWindow);
            EditorWorld.MasterGameWindow = EditorWindow;
            EditorWindow.DockOrder = 3;
            //EditorWindow.Dock = Control.Dockings.Fill;
            EditorWindow.Frame = EditorWindow.Frame;
        }

    }
}
