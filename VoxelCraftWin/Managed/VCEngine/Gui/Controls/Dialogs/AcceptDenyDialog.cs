using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class AcceptDenyDialog : Dialog
    {
        public event EventHandler Accepted = delegate { };
        public event EventHandler Denied = delegate { };
        public Label Text;
        public TextField Field;
        public Button OkButton;
        public Button CancenButton;

        public AcceptDenyDialog(Window window, String label, String acceptText, String denyText) : base(window)
        {
            SetSize(new Point(350, 150));

            Text = new Label(ParentWindow, label);
            Text.Location = new Point(50, 110);
            AddControl(Text);

            Field = new TextField(ParentWindow);
            Field.Frame = new Rectangle(50, 80, 250, Field.Height);
            Field.EnterPressed += (s, a) =>
                {
                    Hide();
                    Accepted(this, EventArgs.Empty);
                };
            AddControl(Field);

            OkButton = new Button(ParentWindow, acceptText);
            OkButton.Frame = new Rectangle(225, 40, 75, OkButton.Height);
            OkButton.GuiStyle = Button.Style.HighlightedButton;
            OkButton.Click += (s, a) =>
            {
                Hide();
                Accepted(this, EventArgs.Empty);
            };
            AddControl(OkButton);

            CancenButton = new Button(ParentWindow, denyText);
            CancenButton.Frame = new Rectangle(150, 40, 70, CancenButton.Height);
            CancenButton.Click += (s, a) =>
            {
                Hide();
                Denied(this, EventArgs.Empty);
            };
            AddControl(CancenButton);
        }

        public override void Display()
        {
            base.Display();
            Field.Text = "";
            Field.Focus();
        } 

        protected override void Draw()
        {
            base.Draw();

            GuiDrawer.DrawBackgroundEmpty(ScreenFrame);
            GuiDrawer.DrawButtonHighlighted(new Rectangle(ScreenFrame.X, ScreenFrame.Y + Height - 5, Width, 5));
            GuiDrawer.DrawButtonHighlighted(new Rectangle(ScreenFrame.X, ScreenFrame.Y, Width, 5));
        }

    }
}
