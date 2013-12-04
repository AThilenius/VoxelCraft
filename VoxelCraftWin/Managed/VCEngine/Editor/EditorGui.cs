using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorGui
    {
        public static MenuBar MainMenuBar;
        public static TabbedContainer InspectorWindow;
        public static VerticalContainer ColorPage;
        public static HslColorPicker ColorPicker;
        public static SolutionExplorer Solution;
        public static TabbedContainer EditorWindow;

        public static void Initialize()
        {
            // Main Control
            Control.MainControl = new Control();
            Control.MainControl.ScreenFrame = new Rectangle(0, 0, Window.Size);
            Control.MainControl.BorderColor = Color.Black;
            Control.MainControl.BackgroundColor = Color.Trasparent;
            Control.MainControl.HoverBackgroundColor = Color.Trasparent;
            Control.MainControl.SetFirstResponder();

            CreateMenuBar();
            CreateInspector();
            CreateEditorWindow();
        }

        private static void CreateMenuBar()
        {
            MainMenuBar = new MenuBar();
            Control.MainControl.AddControl(MainMenuBar);

            Menu testMenu1 = new Menu();
            testMenu1.AddItemReverse("Save").Click += (s, a) =>
                {

                };

            Menu testMenu2 = new Menu();
            testMenu2.AddItemReverse("Options");
            testMenu2.AddItemReverse("Find");
            testMenu2.AddItemReverse("Redo");
            testMenu2.AddItemReverse("Undo");

            MainMenuBar.AddMenu("File", testMenu1);
            MainMenuBar.AddMenu("Options", testMenu2);
        }

        private static void CreateInspector()
        {
            InspectorWindow = new TabbedContainer();
            InspectorWindow.HoverBackgroundColor = InspectorWindow.BackgroundColor;
            InspectorWindow.ScreenFrame = new Rectangle(Window.Size.X - 300, 0, 300, Window.Size.Y - 20);
            Control.MainControl.AddControl(InspectorWindow);
            Window.Resize += (s, a) => InspectorWindow.ScreenFrame = new Rectangle(Window.Size.X - 300, 0, 300, Window.Size.Y - 20);

            ColorPage = new VerticalContainer();
            InspectorWindow.AddTab("Tools", ColorPage);

            DirectoryExporer de = new DirectoryExporer(PathUtilities.AssetsPath);
            InspectorWindow.AddTab("Solution Explorer", de);

            Solution = new SolutionExplorer();
            InspectorWindow.AddTab("Legacy", Solution);

            FillColorControls();
        }

        private static void CreateEditorWindow()
        {
            EditorWindow = new TabbedContainer();
            EditorWindow.BackgroundColor = Color.Trasparent;
            EditorWindow.HoverBackgroundColor = Color.Trasparent;
            EditorWindow.Frame = new Rectangle(0, 0, Window.FullViewport.Width - 300, Window.FullViewport.Height - 20);
            EditorWindow.AlignTop = true;
            Control.MainControl.AddControl(EditorWindow);
            Window.Resize += (s, a) => EditorWindow.Frame = new Rectangle(0, 0, Window.FullViewport.Width - 300, Window.FullViewport.Height - 20);

            // HACK
            EditorWorld.MasterGameWindow = new GameWindow(2);
            Tab tab = EditorWindow.AddTab("Test World", EditorWorld.MasterGameWindow);
            tab.HorizontalPadding = 0;

            // Force a re-fill
            EditorWindow.Frame = EditorWindow.Frame;
        }

        private static void FillColorControls()
        {
            ColorPicker = new HslColorPicker();
            ColorPicker.Frame = new Rectangle(0, 0, 0, 150);
            ColorPage.AddControl(ColorPicker);
            ColorPage.AddPadding();

            VerticalContainer controlsContainer = new VerticalContainer();
            controlsContainer.AddControl(new Label("Tools:"));

            // Controls:
            {
                SelectionButton selectionButton = new SelectionButton("Cube Tool");
                selectionButton.OnSelection += (sender, args) => EditorWorld.MasterGameWindow.ActiveTool = new BlockClickDragTool(EditorWorld.MasterGameWindow);
                controlsContainer.AddControl(selectionButton);

                SelectionButton circleButton = new SelectionButton("Sphere Tool");
                circleButton.OnSelection += (s, a) => EditorWorld.MasterGameWindow.ActiveTool = new CircleTool(EditorWorld.MasterGameWindow);
                controlsContainer.AddControl(circleButton);

                SelectionButton eyeDropButton = new SelectionButton("Eye Dropper Tool");
                eyeDropButton.OnSelection += (sender, args) =>
                    {
                        EyeDropperTool edt = new EyeDropperTool(EditorWorld.MasterGameWindow);
                        edt.OnPicked += (s, a) => ColorPicker.ColorRGB = edt.ColorRGB;
                        EditorWorld.MasterGameWindow.ActiveTool = edt;
                    };
                controlsContainer.AddControl(eyeDropButton);

                SelectionButton.CreateGroup(selectionButton, circleButton, eyeDropButton);
                selectionButton.Activate();
                controlsContainer.Frame = new Rectangle(0, 0, 0, 120);
            }

            ColorPage.AddControl(controlsContainer);

            Button shadowButton = new Button("Hide Shadows");
            shadowButton.Click += (s, a) =>
                {
                    EditorWorld.MasterGameWindow.World.RebuildParams.ShowShadows = !EditorWorld.MasterGameWindow.World.RebuildParams.ShowShadows;
                    EditorWorld.MasterGameWindow.World.RebuildParams.ForceRebuildAll = true;

                    if (EditorWorld.MasterGameWindow.World.RebuildParams.ShowShadows)
                        shadowButton.Text = "Hide Shadows";

                    else
                        shadowButton.Text = "Show Shadows";

                    EditorWorld.MasterGameWindow.World.ReBuild();
                };
            ColorPage.AddControl(shadowButton);
        }

    }
}
