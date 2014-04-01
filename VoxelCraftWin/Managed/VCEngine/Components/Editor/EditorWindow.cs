using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorWindow : Window
    {
        public Header HeaderBar;

        public SolutionDescription Solution;
        public WelcomeMainPage WelcomePage;

        public VerticalControlSpinner MainSpinner;
        public VoxelEditor VoxelEditor;
        public MaterialEditor MaterialEditor;
        public ModelEditor ModelEditor;

        public EditorWindow(int width, int height, String title) : base(width, height, title)
        {
            // Create Header, dock it to main control top, set height 75
            HeaderBar = new Header(this);
            HeaderBar.Layer = 10;
            MainControl.AddControl(HeaderBar);
            HeaderBar.DockOrder = 0;
            HeaderBar.Dock = Control.Dockings.Top;
            HeaderBar.Frame = new Rectangle(0, 0, 0, 75);

            // Create Spinner, pre-size it to fill
            MainSpinner = new VerticalControlSpinner(this);
            MainControl.AddControl(MainSpinner);
            MainSpinner.Frame = new Rectangle(0, 0, ScaledSize.X, ScaledSize.Y - 75);

            // Create Welcome Page, wait to create the rest
            WelcomePage = new VCEngine.WelcomeMainPage(this);
            MainSpinner.AddControl(WelcomePage);
            WelcomePage.Create();
            WelcomePage.OnSolutionReady += (s, a) =>
                {
                    HeaderBar.PagesPicker.AddControl(VoxelEditor);
                    HeaderBar.PagesPicker.AddControl(MaterialEditor);
                    HeaderBar.PagesPicker.AddControl(ModelEditor);

                    MainSpinner.Select(VoxelEditor);
                };

            // Create VoxelEditor, child it to spinner, fill controls
            VoxelEditor = new VCEngine.VoxelEditor(this);
            MainSpinner.AddControl(VoxelEditor);
            VoxelEditor.Create();

            // Create Material, child it to spinner, fill controls
            MaterialEditor = new VCEngine.MaterialEditor(this);
            MainSpinner.AddControl(MaterialEditor);
            MaterialEditor.Create();

            // Create Material, child it to spinner, fill controls
            ModelEditor = new VCEngine.ModelEditor(this);
            MainSpinner.AddControl(ModelEditor);
            ModelEditor.Create();

            // Dock the spinner to remaining area
            MainSpinner.DockOrder = 1;
            MainSpinner.Dock = Control.Dockings.Fill;

            // Resize All
            MainControl.Frame = MainControl.Frame;
        }
        
    }
}
