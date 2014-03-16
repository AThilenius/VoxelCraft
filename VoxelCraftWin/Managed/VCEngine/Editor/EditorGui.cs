using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorGui
    {
        public static Header HeaderBar;
        public static VerticalControlSpinner MainSpinner;
        public static VoxelEditor VoxelEditor;
        public static MaterialEditor MaterialEditor;

        public static void Initialize()
        {
            // Main Control
            Control.MainControl = new Control();
            Control.MainControl.ScreenFrame = new Rectangle(0, 0, Editor.MainWindow.ScaledSize);
            Control.MainControl.SetFirstResponder();

            // Create Header, dock it to main control top, set height 75
            HeaderBar = new Header();
            HeaderBar.Layer = 10;
            Control.MainControl.AddControl(HeaderBar);
            HeaderBar.DockOrder = 0;
            HeaderBar.Dock = Control.Dockings.Top;
            HeaderBar.Frame = new Rectangle(0, 0, 0, 75);

            // Create Spinner, pre-size it to fill
            MainSpinner = new VerticalControlSpinner();
            Control.MainControl.AddControl(MainSpinner);
            MainSpinner.Frame = new Rectangle(0, 0, Editor.MainWindow.ScaledSize.X, Editor.MainWindow.ScaledSize.Y - 75);

            // Create VoxelEditor, child it to spinner, fill controls
            VoxelEditor = new VCEngine.VoxelEditor();
            MainSpinner.AddControl(VoxelEditor);
            VoxelEditor.Create();

            // Create Material, child it to spinner, fill controls
            MaterialEditor = new VCEngine.MaterialEditor();
            MainSpinner.AddControl(MaterialEditor);
            
            // Dock the spinner to remaining area
            MainSpinner.DockOrder = 1;
            MainSpinner.Dock = Control.Dockings.Fill;

            // Resize All
            Control.MainControl.Frame = Control.MainControl.Frame;
        }
        
    }
}
