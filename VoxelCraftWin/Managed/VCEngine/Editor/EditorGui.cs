using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorGui
    {
        public static Header HeaderBar;
        public static TabbedContainer InspectorWindow;
        public static VerticalContainer ColorPage;
        public static HslColorPicker ColorPicker;
        public static GameWindow EditorWindow;

        public static void Initialize()
        {
            // Main Control
            Control.MainControl = new Control();
            Control.MainControl.ScreenFrame = new Rectangle(0, 0, Window.ScaledSize);
            Control.MainControl.BorderColor = Color.Black;
            Control.MainControl.BackgroundColor = Color.Trasparent;
            Control.MainControl.HoverBackgroundColor = Color.Trasparent;
            Control.MainControl.SetFirstResponder();

            CreateMenuBar();
            CreateInspector();
            CreateSolutionExplorer();
            CreateEditorWindow();
        }

        private static void CreateMenuBar()
        {
            HeaderBar = new Header();
            Control.MainControl.AddControl(HeaderBar);
            HeaderBar.Dock = Control.Dockings.Top;
            HeaderBar.DockOrder = 0;
            HeaderBar.Frame = new Rectangle(0, 0, 0, 75);
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

        private static void CreateInspector()
        {
            InspectorWindow = new TabbedContainer();
            Control.MainControl.AddControl(InspectorWindow);
            InspectorWindow.HoverBackgroundColor = InspectorWindow.BackgroundColor;
            InspectorWindow.Dock = Control.Dockings.Right;
            InspectorWindow.DockOrder = 1;
            InspectorWindow.Frame = new Rectangle(0, 0, 250, 0);

            ColorPage = new VerticalContainer();
            ColorPage.BorderColor = Color.ControlRed;
            ColorPage.BorderWidth = 5;
            InspectorWindow.AddTab("Tools", ColorPage);

            FillColorControls();
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

        private static void FillColorControls()
        {
            ColorPicker = new HslColorPicker();
            ColorPicker.Frame = new Rectangle(0, 0, 0, 150);
            ColorPage.AddControl(ColorPicker);
            ColorPage.AddPadding();
            ColorPage.AddControl(new Label(""));
            ColorPage.AddControl(new Label("Tools:"));

            SelectionButton selectionButton = new SelectionButton("Cube Tool");
            selectionButton.OnSelection += (sender, args) => EditorWorld.MasterGameWindow.ActiveTool = new BlockClickDragTool(EditorWorld.MasterGameWindow);
            ColorPage.AddControl(selectionButton);

            SelectionButton circleButton = new SelectionButton("Sphere Tool");
            circleButton.OnSelection += (s, a) => EditorWorld.MasterGameWindow.ActiveTool = new CircleTool(EditorWorld.MasterGameWindow);
            ColorPage.AddControl(circleButton);

            SelectionButton eyeDropButton = new SelectionButton("Eye Dropper Tool");
            eyeDropButton.OnSelection += (sender, args) =>
                {
                    EyeDropperTool edt = new EyeDropperTool(EditorWorld.MasterGameWindow);
                    edt.OnPicked += (s, a) => ColorPicker.ColorRGB = edt.ColorRGB;
                    EditorWorld.MasterGameWindow.ActiveTool = edt;
                };
            ColorPage.AddControl(eyeDropButton);

            SelectionButton.CreateGroup(selectionButton, circleButton, eyeDropButton);
            selectionButton.Activate();
            //ColorPage.Frame = new Rectangle(0, 0, 0, 120);

            Button shadowButton = new Button("Hide Shadows");
            shadowButton.Click += (s, a) =>
                {
                    EditorWorld.MasterGameWindow.World.RebuildParams.ShowShadows = !EditorWorld.MasterGameWindow.World.RebuildParams.ShowShadows;
                    EditorWorld.MasterGameWindow.World.RebuildParams.ForceRebuildAll = true;

                    if (EditorWorld.MasterGameWindow.World.RebuildParams.ShowShadows)
                        shadowButton.Text.Text = "Hide Shadows";

                    else
                        shadowButton.Text.Text = "Show Shadows";

                    EditorWorld.MasterGameWindow.World.ReBuild();
                };
            ColorPage.AddControl(shadowButton);
        }

    }
}
