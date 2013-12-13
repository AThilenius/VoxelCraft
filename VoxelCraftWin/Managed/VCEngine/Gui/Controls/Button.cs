using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Button : Control
    {

        public Label Text;
        
        public Button(String title)
        {
            Text = new Label(title);
            AddControl(Text);
            Text.TextAlignment = Label.TextAlignments.Center;
            Text.Dock = Dockings.Fill;

            Frame = new Rectangle(0, 0, Font.GetMetrics(title).TotalWidth, Font.GetMetrics(title).TotalHeight);
            DrawHover = true;
            BorderWidth = 1;
        }

        protected override void Draw()
        {
            base.Draw();

            if (Enabled)
            {
                Gui.DrawBackground(ScreenFrame);
                //Gui.DrawString(Text, new Point(ScreenFrame.X + 10, ScreenFrame.Y + 3), TextColor, Font);
            }

            else
            {
                Gui.DrawBackgroundEmpty(ScreenFrame);
                //Gui.DrawString(Text, new Point(ScreenFrame.X + 10, ScreenFrame.Y + 3), Color.ControlDisabledText, Font);
            }
        }

    }
}
