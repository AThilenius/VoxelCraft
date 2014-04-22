using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class WelcomeLeftPane : Control
    {
        public Label TitleLabel;
        public Label SubTitleLabel;

        public Label StartLabel;
        public Button CreateNewButton;
        public Button OpenButton;

        public Label RecentLabel;

        public event EventHandler OnCreateProjectClicked = delegate { };
        public event EventHandler OnOpenProjectClicked = delegate { };

        private List<Button> m_recentButtons = new List<Button>();

        public WelcomeLeftPane(Window window) : base(window)
        {
            TitleLabel = new Label(window, "VC Engine Core");
            TitleLabel.Font = Font.GetFont("Calibri", 26, window);
            TitleLabel.FontColor = Color.White;
            TitleLabel.TextAlignment = Label.TextAlignments.LowerLeft;
            AddControl(TitleLabel);

            SubTitleLabel = new Label(window, "Thilenius");
            SubTitleLabel.FontColor = Color.White;
            SubTitleLabel.TextAlignment = Label.TextAlignments.LowerLeft;
            AddControl(SubTitleLabel);

            StartLabel = new Label(window, "Start");
            StartLabel.Font = Font.GetFont("Calibri", 20, window);
            StartLabel.FontColor = Color.Black;
            StartLabel.TextAlignment = Label.TextAlignments.LowerLeft;
            AddControl(StartLabel);

            CreateNewButton = new Button(window, "New Solution");
            CreateNewButton.GuiStyle = Button.Style.LabelButton;
            CreateNewButton.Click += (s, a) => OnCreateProjectClicked(this, EventArgs.Empty);
            AddControl(CreateNewButton);

            OpenButton = new Button(window, "Open Solution");
            OpenButton.GuiStyle = Button.Style.LabelButton;
            OpenButton.Click += (s, a) => OnOpenProjectClicked(this, EventArgs.Empty);
            AddControl(OpenButton);

            RecentLabel = new Label(window, "Recent");
            RecentLabel.Font = Font.GetFont("Calibri", 20, window);
            RecentLabel.FontColor = Color.Black;
            RecentLabel.TextAlignment = Label.TextAlignments.LowerLeft;
            AddControl(RecentLabel);

            Resize += (s, a) => ResizeHandler();
        }

        public void AddRecent(RecentProject proj)
        {
            Button button = new Button(ParentWindow, proj.Name);
            button.GuiStyle = Button.Style.LabelButton;
            button.Click += (s, a) => Project.LoadProject(proj.FullPath);
            AddControl(button);
            m_recentButtons.Add(button);
        }

        private void ResizeHandler()
        {
            TitleLabel.Frame = new Rectangle(20, Height - 35, Width - 40, 20);
            SubTitleLabel.Frame = new Rectangle(20, Height - 55, Width - 40, 10);

            StartLabel.Frame = new Rectangle(20, Height - 120, Width - 40, 20);
            CreateNewButton.Frame = new Rectangle(0, Height - 140, Width, 20);
            OpenButton.Frame = new Rectangle(0, Height - 160, Width, 20);

            RecentLabel.Frame = new Rectangle(20, Height - 220, Width - 40, 20);

            for ( int i = 0; i < m_recentButtons.Count; i++ )
            {
                Button button = m_recentButtons[i];
                button.Frame = new Rectangle(0, Height - (240 + i * 20), Width, 20);
            }
        }

        protected override void Draw()
        {
            base.Draw();

            Gui.DrawButtonHighlighted(new Rectangle(0, Height - 70, Width, 70));
            Gui.DrawBackground(new Rectangle(0, 0, Width, Height - 70));
        }

    }
}
