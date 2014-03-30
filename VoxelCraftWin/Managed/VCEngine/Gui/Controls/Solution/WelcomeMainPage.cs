using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class SolutionReadyEventArgs : EventArgs
    {
        public SolutionDescription Solution;

        public SolutionReadyEventArgs(SolutionDescription solution)
        {
            Solution = solution;
        }
    }

    public class WelcomeMainPage : MainPageBase
    {
        public WelcomeLeftPane WelcomePane;
        public event EventHandler<SolutionReadyEventArgs> OnSolutionReady = delegate { };

        public override string Name { get { return "Welcome"; } }

        protected override Control LeftPane { get { return WelcomePane; } }
        protected override Control RightPane { get { return null; } }
        protected override Control CenterPane { get { return null; } }
        protected override Control LowerPane { get { return null; } }

        public WelcomeMainPage(Window window) : base(window)
        {
            WelcomePane = new WelcomeLeftPane(window);
            WelcomePane.OnCreateProjectClicked += (s, a) => OnSolutionReady(this, new SolutionReadyEventArgs(null));
            WelcomePane.OnOpenProjectClicked += (s, a) => OnSolutionReady(this, new SolutionReadyEventArgs(null));
            AddControl(WelcomePane);
            base.OnSelected();
        }

        public void Create()
        {

        }

    }
}
