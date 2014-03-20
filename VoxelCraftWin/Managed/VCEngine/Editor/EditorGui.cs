using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorGui : Window
    {
        public static Header HeaderBar;
        public static VerticalControlSpinner MainSpinner;
        public static VoxelEditor VoxelEditor;
        public static MaterialEditor MaterialEditor;

        public EditorGui(int width, int height, String title) : base(width, height, title)
        {
        }

        public override void FinishInitialization()
        {
            base.FinishInitialization();

            // Create Header, dock it to main control top, set height 75
            HeaderBar = new Header(this);
            HeaderBar.Layer = 10;
            Control.MainControl.AddControl(HeaderBar);
            HeaderBar.DockOrder = 0;
            HeaderBar.Dock = Control.Dockings.Top;
            HeaderBar.Frame = new Rectangle(0, 0, 0, 75);

            // Create Spinner, pre-size it to fill
            MainSpinner = new VerticalControlSpinner(this);
            Control.MainControl.AddControl(MainSpinner);
            MainSpinner.Frame = new Rectangle(0, 0, ScaledSize.X, ScaledSize.Y - 75);

            // Create VoxelEditor, child it to spinner, fill controls
            VoxelEditor = new VCEngine.VoxelEditor(this);
            MainSpinner.AddControl(VoxelEditor);
            VoxelEditor.Create();

            // Create Material, child it to spinner, fill controls
            MaterialEditor = new VCEngine.MaterialEditor(this);
            MainSpinner.AddControl(MaterialEditor);

            // Dock the spinner to remaining area
            MainSpinner.DockOrder = 1;
            MainSpinner.Dock = Control.Dockings.Fill;

            // Resize All
            Control.MainControl.Frame = Control.MainControl.Frame;
        }
        
    }
}
