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
            MenuButton,
            ImageButton,
            LabelButton,
            TriButtonLeft,
            TriButtonRight,
            TriButtonCenter
        }

        public Label Text;
        public Texture Image;
        public Style GuiStyle = Style.PushButton;
        
        public Button(Window window, String title) : base(window)
        {
            Text = new Label(ParentWindow, title);
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
                        Text.FontColor = Color.Black;

                        if (IsClickDown)
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.ButtonDown, ScreenFrame);

                        else
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.Button, ScreenFrame);
                    }

                    else
                        Gui.DrawBackgroundEmpty(ScreenFrame);

                    break;

                case Style.HighlightedButton:
                    if (Enabled)
                    {
                        Text.FontColor = Color.White;

                        if (IsClickDown)
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.ButtonHighlightDown, ScreenFrame);

                        else
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.ButtonHighlight, ScreenFrame);
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

                case Style.ImageButton:
                    if (Enabled)
                    {
                        Rectangle sf = ScreenFrame;

                        if (IsClickDown)
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.ButtonDown, sf);
                        else
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.Button, sf);

                        Gui.DrawImage(Image, new Rectangle(sf.X + 5, sf.Y + 5, sf.Width - 10, sf.Height - 10));
                    }

                    else
                        Gui.DrawBackgroundEmpty(ScreenFrame);
                    break;

                case Style.LabelButton:
                        Text.BevelText = false;

                        if (IsClickDown)
                        {
                            Gui.DrawButtonHighlighted(ScreenFrame);
                            Text.FontColor = Color.White;
                        }
                        else
                        {
                            if (IsHovered)
                            {
                                Gui.DrawButtonAccentuated(ScreenFrame);
                                Text.FontColor = Color.White;
                            }
                            else
                            {
                                Text.FontColor = Color.ControlBlue;
                            }
                        }
                    break;
            }
            
        }



    }
}
