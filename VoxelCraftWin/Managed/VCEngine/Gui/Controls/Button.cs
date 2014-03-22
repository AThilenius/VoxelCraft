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
                            GuiDrawer.Draw9SliceImage(Gui.StandardTextures.ButtonDown, ScreenFrame);

                        else
                            GuiDrawer.Draw9SliceImage(Gui.StandardTextures.Button, ScreenFrame);
                    }

                    else
                        GuiDrawer.DrawBackgroundEmpty(ScreenFrame);

                    break;

                case Style.HighlightedButton:
                    if (Enabled)
                    {
                        Text.FontColor = Color.White;

                        if (IsClickDown)
                            GuiDrawer.Draw9SliceImage(Gui.StandardTextures.ButtonHighlightDown, ScreenFrame);

                        else
                            GuiDrawer.Draw9SliceImage(Gui.StandardTextures.ButtonHighlight, ScreenFrame);
                    }

                    else
                    {
                        Text.FontColor = Color.Black;
                        GuiDrawer.DrawBackgroundEmpty(ScreenFrame);
                    }
                    break;

                case Style.MenuButton:
                    if (IsHovered)
                    {
                        GuiDrawer.DrawButtonHighlighted(ScreenFrame);
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
                            GuiDrawer.Draw9SliceImage(Gui.StandardTextures.ButtonDown, sf);
                        else
                            GuiDrawer.Draw9SliceImage(Gui.StandardTextures.Button, sf);

                        GuiDrawer.DrawImage(Image, new Rectangle(sf.X + 5, sf.Y + 5, sf.Width - 10, sf.Height - 10));
                    }

                    else
                        GuiDrawer.DrawBackgroundEmpty(ScreenFrame);
                    break;
            }
            
        }



    }
}
