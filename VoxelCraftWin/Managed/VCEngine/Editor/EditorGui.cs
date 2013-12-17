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
        public static VerticalContainer ContectMenu;

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
            //Control.MainControl.Frame = Control.MainControl.Frame;
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
            ContectMenu = new VerticalContainer();
            Control.MainControl.AddControl(ContectMenu);

            ContectMenu.DockOrder = 1;
            ContectMenu.Dock = Control.Dockings.Right;
            ContectMenu.Width = 250;
            //ContectMenu.Height = 0;
            //ContectMenu.Frame = new Rectangle(Window.ScaledSize.X - 250, 0, 250, Window.ScaledSize.Y);

            ColorPicker = new HslColorPicker();
            ColorPicker.Height = 100;
            ContectMenu.AddControl(ColorPicker);
            ContectMenu.AddControl(new Label(""));
            ContectMenu.AddControl(new Label("Tools:"));

            SelectionButton selectionButton = new SelectionButton("Cube Tool");
            selectionButton.OnSelection += (sender, args) => EditorWorld.MasterGameWindow.ActiveTool = new BlockClickDragTool(EditorWorld.MasterGameWindow);
            ContectMenu.AddControl(selectionButton);

            ContectMenu.AddControl(new Label("Test"));

            //SelectionButton circleButton = new SelectionButton("Sphere Tool");
            //circleButton.OnSelection += (s, a) => EditorWorld.MasterGameWindow.ActiveTool = new CircleTool(EditorWorld.MasterGameWindow);
            //ContectMenu.AddControl(circleButton);

            //SelectionButton eyeDropButton = new SelectionButton("Eye Dropper Tool");
            //eyeDropButton.OnSelection += (sender, args) =>
            //{
            //    EyeDropperTool edt = new EyeDropperTool(EditorWorld.MasterGameWindow);
            //    edt.OnPicked += (s, a) => ColorPicker.ColorRGB = edt.ColorRGB;
            //    EditorWorld.MasterGameWindow.ActiveTool = edt;
            //};
            //ContectMenu.AddControl(eyeDropButton);

            //SelectionButton.CreateGroup(selectionButton, circleButton, eyeDropButton);
            //selectionButton.Activate();
            ////ColorPage.Frame = new Rectangle(0, 0, 0, 120);

            //Button shadowButton = new Button("Hide Shadows");
            //shadowButton.Click += (s, a) =>
            //{
            //    EditorWorld.MasterGameWindow.World.RebuildParams.ShowShadows = !EditorWorld.MasterGameWindow.World.RebuildParams.ShowShadows;
            //    EditorWorld.MasterGameWindow.World.RebuildParams.ForceRebuildAll = true;

            //    if (EditorWorld.MasterGameWindow.World.RebuildParams.ShowShadows)
            //        shadowButton.Text.Text = "Hide Shadows";

            //    else
            //        shadowButton.Text.Text = "Show Shadows";

            //    EditorWorld.MasterGameWindow.World.ReBuild();
            //};
            //ContectMenu.AddControl(shadowButton);

            //ContectMenu.Width = 250;
            //Control.MainControl.Frame = Control.MainControl.Frame;
            ContectMenu.Rebuild();
        }

        private static void CreateSolutionExplorer()
        {
            SolutionExplorer se = new SolutionExplorer();
            Control.MainControl.AddControl(se);
            se.DockOrder = 2;
            se.Dock = Control.Dockings.Left;
            se.AddProject("Love Monkey Game", PathUtilities.AssetsPath);
            se.Frame = new Rectangle(0, 0, 250, 0);
        }

        private static void CreateEditorWindow()
        {
            // HACK
            EditorWindow = new GameWindow(2);
            Control.MainControl.AddControl(EditorWindow);
            EditorWorld.MasterGameWindow = EditorWindow;
            EditorWindow.DockOrder = 3;
            EditorWindow.Dock = Control.Dockings.Fill;
            EditorWindow.Frame = EditorWindow.Frame;
        }

    }
}
