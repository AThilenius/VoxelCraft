﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ProjectHeader : Control
    {
        public Label Text;
        public ExpandButton ExpandButton;
        public Button ExplorerButton;
        public ProjectExplorer Project;

        public ProjectHeader(String projectName, ProjectExplorer project)
        {
            Project = project;

            ExpandButton = new ExpandButton();
            AddControl(ExpandButton);
            ExpandButton.IsExpanded = true;
            ExpandButton.Frame = new Rectangle(5, 16, 8, 8);
            ExpandButton.BackgroundColor = new Color(112, 126, 140, 255);

            Text = new Label(projectName);
            AddControl(Text);
            Text.IsEventPassthrough = true;
            Text.Dock = Dockings.Fill;
            Text.TextAlignment = Label.TextAlignments.Center;
            DoubleClick += (s, a) => ExpandButton.ToggleExpandContract();

            Height = 40;
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            Gui.DrawBackgroundEmpty(ScreenFrame, false);
            Gui.DrawImage(@"Icons\Folder.DDS", new Rectangle(sf.X + 30, sf.Y + 5, 30, 30));
        }

    }
}
