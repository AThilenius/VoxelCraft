using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class PanelsTrippleButton : Control
    {
        public ToggleButton LeftButton;
        public ToggleButton CenterButton;
        public ToggleButton RightButton;

        public PanelsTrippleButton(Window window) : base(window)
        {
            // Left
            LeftButton = new ToggleButton(ParentWindow, " ");
            LeftButton.ImagePath = @"Icons\LeftPane.DDS";
            LeftButton.Width = 30;
            LeftButton.Style = ToggleButton.ToggleStyle.TriLeft;
            LeftButton.IsDepressed = true;
            AddControl(LeftButton);

            // Center
            CenterButton = new ToggleButton(ParentWindow, " ");
            CenterButton.ImagePath = @"Icons\CenterPane.DDS";
            CenterButton.Width = 30;
            CenterButton.Style = ToggleButton.ToggleStyle.TriCenter;
            CenterButton.IsDepressed = true;
            AddControl(CenterButton);

            // Right
            RightButton = new ToggleButton(ParentWindow, " ");
            RightButton.Width = 30;
            RightButton.ImagePath = @"Icons\RightPane.DDS";
            RightButton.Style = ToggleButton.ToggleStyle.TriRight;
            RightButton.IsDepressed = true;
            AddControl(RightButton);

            Resize += (s, a) => ResizeHandler();
            ResizeHandler();
            Height = LeftButton.Height;
            Width = LeftButton.Width + RightButton.Width + CenterButton.Width;
        }

        private void ResizeHandler()
        {
            LeftButton.Frame = new Rectangle(0, 0, 30, LeftButton.Height);
            CenterButton.Frame = new Rectangle(27, 0, 30, CenterButton.Height);
            RightButton.Frame = new Rectangle(54, 0, 30, RightButton.Height);
        }

    }
}
