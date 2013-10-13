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

        public static void Initialize()
        {
            // Main Control
            Control.MainControl = new Control();
            Control.MainControl.ScreenFrame = new Rectangle(0, 0, Window.Size);
            Control.MainControl.BorderColor = Color.Black;
            Control.MainControl.BackgroundColor = Color.Trasparent;
            Control.MainControl.HighlightBackgroundColor = Color.Trasparent;
            Control.MainControl.SetFirstResponder();

            CreateMenuBar();
            CreateInspector();
        }

        private static void FillColorControls()
        {
            ColorPicker = new HslColorPicker();
            ColorPicker.Frame = new Rectangle(0, 0, 0, 150);
            ColorPage.AddControl(ColorPicker);
        }

        private static void CreateInspector()
        {
            InspectorWindow = new TabbedContainer();
            InspectorWindow.HighlightBackgroundColor = InspectorWindow.BackgroundColor;
            InspectorWindow.ScreenFrame = new Rectangle(Window.Size.X - 300, 0, 300, Window.Size.Y - 20);
            Control.MainControl.AddControl(InspectorWindow);

            ColorPage = new VerticalContainer();
            ColorPage.BorderColor = Color.ControlBorder;
            ColorPage.BorderWidth = 1;
            ColorPage.HighlightBackgroundColor = ColorPage.BackgroundColor;
            InspectorWindow.AddTab("Colors", ColorPage);

            Diagnostics = new DiagnosticsPane();
            Diagnostics.HighlightBackgroundColor = Diagnostics.BackgroundColor;
            InspectorWindow.AddTab("Diagnostics", Diagnostics);

            FillColorControls();
        }

        private static void CreateMenuBar()
        {
            MainMenuBar = new MenuBar();
            Control.MainControl.AddControl(MainMenuBar);

            Menu testMenu1 = new Menu();
            Control.MainControl.AddControl(testMenu1);
            testMenu1.AddItemReverse("Close");
            testMenu1.AddItemReverse("Open");
            testMenu1.AddItemReverse("Save");

            Menu testMenu2 = new Menu();
            Control.MainControl.AddControl(testMenu2);
            testMenu2.AddItemReverse("Options");
            testMenu2.AddItemReverse("Find");
            testMenu2.AddItemReverse("Redo");
            testMenu2.AddItemReverse("Undo");

            MainMenuBar.AddMenu("File", testMenu1);
            MainMenuBar.AddMenu("Options", testMenu2);
        }

    }
}
