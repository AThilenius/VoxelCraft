using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Button : Control
    {
        public enum Style
        {
            PushButton,
            HighlightedButton,
            MenuButton
        }

        public Label Text;
        public Style GuiStyle = Style.PushButton;
        
        public Button(String title)
        {
            Text = new Label(title);
            Text.IsEventPassthrough = true;
            AddControl(Text);
            Text.TextAlignment = Label.TextAlignments.Center;
            Text.Dock = Dockings.Fill;

            Frame = new Rectangle(0, 0, Font.GetMetrics(title).TotalWidth + 20, Font.GetMetrics(title).TotalHeight + 10);
        }

        protected override void Draw()
        {
            switch (GuiStyle)
            {
                case Style.PushButton:
                    if (Enabled)
                    {
                        if (IsClickDown)
                            Gui.Draw9Slice(@"Icons\ButtonDown.DDS", ScreenFrame);

                        else
                            Gui.Draw9Slice(@"Icons\Button.DDS", ScreenFrame);
                    }

                    else
                        Gui.DrawBackgroundEmpty(ScreenFrame);

                    break;

                case Style.HighlightedButton:
                    if (Enabled)
                    {
                        Text.FontColor = Color.White;

                        if (IsClickDown)
                            Gui.Draw9Slice(@"Icons\ButtonHighlightDown.DDS", ScreenFrame);

                        else
                            Gui.Draw9Slice(@"Icons\ButtonHighlight.DDS", ScreenFrame);
                    }

                    else
                    {
                        Text.FontColor = Color.Black;
                        Gui.DrawBackgroundEmpty(ScreenFrame);
                    }
                    break;

                case Style.MenuButton:
                    if (IsHovered)
                    {
                        Gui.DrawButtonHighlighted(ScreenFrame);
                        Text.FontColor = Color.White;
                    }

                    else
                        Text.FontColor = Color.Black;

                    break;
            }
            
        }



    }
}
