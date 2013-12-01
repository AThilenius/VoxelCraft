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
        public static DiagnosticsPane Diagnostics;
        public static SolutionExplorer Solution;
        public static Slider RandomColorFactor;

        // Debug
        private static TextField m_text;

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
        }

        private static void FillColorControls()
        {
            ColorPicker = new HslColorPicker();
            ColorPicker.Frame = new Rectangle(0, 0, 0, 150);
            ColorPage.AddControl(ColorPicker);

            VerticalContainer controlsContainer = new VerticalContainer();
            controlsContainer.AddControl(new Label("Controls:"));

            // Controls:
            {
                SelectionButton selectionButton = new SelectionButton("Selection");
                selectionButton.OnSelection += (sender, args) => EditorWorld.MasterGameWindow.ActiveTool = new BlockClickDragTool(EditorWorld.MasterGameWindow);
                controlsContainer.AddControl(selectionButton);

                SelectionButton circleButton = new SelectionButton("Circle Tool");
                circleButton.OnSelection += (s, a) => EditorWorld.MasterGameWindow.ActiveTool = new CircleTool(EditorWorld.MasterGameWindow);
                controlsContainer.AddControl(circleButton);

                SelectionButton eyeDropButton = new SelectionButton("Eye Dropper");
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

            ColorPage.AddControl(new Label("Random Multiplier:"));
            RandomColorFactor = new Slider { Value = 0.1f };
            ColorPage.AddControl(RandomColorFactor);
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

            Solution = new SolutionExplorer();
            InspectorWindow.AddTab("Solution Explorer", Solution);

            Diagnostics = new DiagnosticsPane();
            Diagnostics.HoverBackgroundColor = Diagnostics.BackgroundColor;
            InspectorWindow.AddTab("Diagnostics", Diagnostics);

            FillColorControls();


            // DEBUG
            TreeView tv = new TreeView();
            InspectorWindow.AddTab("Test Tree", tv);

            TreeViewItem tvi1 = new TreeViewItem(tv, null); tv.AddItem(tvi1); tvi1.Text = "Head";

            TreeViewItem tvi2 = new TreeViewItem(tv, tvi1); tvi1.AddChildItem(tvi2); tvi2.Text = "Child Level 1 - 1";
            TreeViewItem tvi3 = new TreeViewItem(tv, tvi1); tvi1.AddChildItem(tvi3); tvi3.Text = "Child Level 1 - 2";
            TreeViewItem tvi4 = new TreeViewItem(tv, tvi1); tvi1.AddChildItem(tvi4); tvi4.Text = "Child Level 1 - 3";

            TreeViewItem tvi5 = new TreeViewItem(tv, tvi3); tvi3.AddChildItem(tvi5); tvi5.Text = "Child Level 2 - 1";
            TreeViewItem tvi6 = new TreeViewItem(tv, tvi3); tvi3.AddChildItem(tvi6); tvi6.Text = "Child Level 2 - 2";

            tv.NotfyUpdate();
        }

        private static void CreateMenuBar()
        {
            MainMenuBar = new MenuBar();
            Control.MainControl.AddControl(MainMenuBar);

            Menu testMenu1 = new Menu();
            testMenu1.AddItemReverse("Close");
            testMenu1.AddItemReverse("Open");
            testMenu1.AddItemReverse("Save");

            Menu testMenu2 = new Menu();
            testMenu2.AddItemReverse("Options");
            testMenu2.AddItemReverse("Find");
            testMenu2.AddItemReverse("Redo");
            testMenu2.AddItemReverse("Undo");

            MainMenuBar.AddMenu("File", testMenu1);
            MainMenuBar.AddMenu("Options", testMenu2);
        }

    }
}
