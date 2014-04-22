using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorWindow : Window
    {
        public Header HeaderBar;

        public WelcomeMainPage WelcomePage;

        public VerticalControlSpinner MainSpinner;
        public VoxelEditor VoxelEditor;
        public MaterialEditor MaterialEditor;
        public ModelEditor ModelEditor;

        public EditorWindow(int width, int height, String title) : base(width, height, title)
        {
            // Create Header
            HeaderBar = new Header(this);
            HeaderBar.Layer = 10;
            MainControl.AddControl(HeaderBar);
            HeaderBar.Frame = new Rectangle(0, ScaledSize.Y - 75, ScaledSize.X, 75);
            Resize += (s, a) => HeaderBar.Frame = new Rectangle(0, ScaledSize.Y - 75, ScaledSize.X, 75);

            // Create Spinner
            MainSpinner = new VerticalControlSpinner(this);
            MainControl.AddControl(MainSpinner);
            MainSpinner.Frame = new Rectangle(0, 0, ScaledSize.X, ScaledSize.Y - 75);
            Resize += (s, a) => MainSpinner.Frame = new Rectangle(0, 0, ScaledSize.X, ScaledSize.Y - 75);

            // Create Welcome Page, wait to create the rest
            WelcomePage = new VCEngine.WelcomeMainPage(this);
            MainSpinner.AddControl(WelcomePage);
            WelcomePage.Create();
            Project.OnProjectLoaded += (s, a) =>
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

            // Resize All
            MainControl.Frame = MainControl.Frame;
        }
        
    }
}
