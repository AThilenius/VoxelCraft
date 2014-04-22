using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class WelcomeMainPage : MainPageBase
    {
        public WelcomeLeftPane WelcomePane;

        public override string Name { get { return "Welcome"; } }

        protected override Control LeftPane { get { return WelcomePane; } }
        protected override Control RightPane { get { return null; } }
        protected override Control CenterPane { get { return null; } }
        protected override Control LowerPane { get { return null; } }

        public WelcomeMainPage(Window window) : base(window)
        {
            WelcomePane = new WelcomeLeftPane(window);
            WelcomePane.OnCreateProjectClicked += (s, a) =>
                {
                    Project.CreateEmpty(@"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\DevelopmentProjects\Battlefield\Battlefield." + PathUtilities.ProjectExtension, "Battlefield");
                };
            //WelcomePane.OnOpenProjectClicked += (s, a) => OnSolutionReady(this, new ProjectReadyEventArgs { Project = null });

            // Add recent projects to the left welcome pane
            String recentJsonPath = PathUtilities.Combine(PathUtilities.WorkingDirectory, "Recent.VCJson");

            if (File.Exists(recentJsonPath))
            {
                RecentProjectsList recentList = JsonConvert.DeserializeObject<RecentProjectsList>(File.ReadAllText(recentJsonPath));
                foreach (RecentProject recProj in recentList.RecentProjects.Values)
                    WelcomePane.AddRecent(recProj);
            }

            AddControl(WelcomePane);
            base.OnSelected();
        }

        public void Create()
        {

        }

    }
}
