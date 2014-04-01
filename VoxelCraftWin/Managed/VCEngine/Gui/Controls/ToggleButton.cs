using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ToggleButton : Control
    {
        public enum ToggleStyle
        {
            Standard,
            TriLeft,
            TriCenter,
            TriRight
        }

        public Label Text;
        public Texture Image;
        public ToggleStyle Style = ToggleStyle.Standard;
        public Boolean IsDepressed;

        public event EventHandler OnDepressed = delegate { };
        public event EventHandler OnRelease = delegate { };

        private List<ToggleButton> m_group = new List<ToggleButton>();

        public ToggleButton(Window window, String title) : base(window)
        {
            Text = new Label(ParentWindow, title);
            Text.IsEventPassthrough = true;
            AddControl(Text);
            Text.TextAlignment = Label.TextAlignments.Center;
            Text.Dock = Dockings.Fill;

            Frame = new Rectangle(0, 0, Font.GetMetrics(title).TotalWidth + 20, Font.GetMetrics(title).TotalHeight + 10);

            Click += (s, a) =>
                {
                    // Treat as Toggle
                    if (m_group.Count == 0)
                    {
                        IsDepressed = !IsDepressed;

                        if (IsDepressed)
                            OnDepressed(this, EventArgs.Empty);

                        else
                            OnRelease(this, EventArgs.Empty);
                    }

                    // Treat as group
                    else
                        Activate(true);
                };
        }

        public void Activate(bool invokeCallback = false)
        {
            if (m_group != null)
            {
                foreach (ToggleButton button in m_group)
                {
                    if (button == this)
                        continue;

                    if (button.IsDepressed && invokeCallback)
                    {
                        button.IsDepressed = false;
                        button.OnRelease(this, EventArgs.Empty);
                    }

                    button.IsDepressed = false;
                }
            }

            if (!IsDepressed && invokeCallback)
            {
                IsDepressed = true;
                OnDepressed(this, EventArgs.Empty);
            }

            IsDepressed = true;
        }

        public static void CreateGroup(params ToggleButton[] buttons)
        {
            List<ToggleButton> group = new List<ToggleButton>(buttons);

            foreach (ToggleButton button in buttons)
                button.m_group = group;
        }

        protected override void Draw()
        {
            switch (Style)
            {
                case ToggleStyle.Standard:
                    if (IsDepressed)
                    {
                        Text.FontColor = Color.White;
                        Gui.Draw9SliceImage(GuiDrawer.StandardTextures.ButtonDown, ScreenFrame);
                    }

                    else
                    {
                        Text.FontColor = Color.Black;
                        Gui.Draw9SliceImage(GuiDrawer.StandardTextures.Button, ScreenFrame);
                    }

                    break;

                case ToggleStyle.TriLeft:
                    if (IsDepressed)
                    {
                        if (m_group.Count == 0)
                        {
                            Text.FontColor = Color.Black;
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.TriButtonLeftDown, ScreenFrame);
                        }

                        else
                        {
                            Text.FontColor = Color.White;
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.TriButtonLeftHighlight, ScreenFrame);
                        }
                    }

                    else
                    {
                            Text.FontColor = Color.Black;
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.TriButtonLeft, ScreenFrame);
                    }
                    break;

                case ToggleStyle.TriCenter:
                    if (IsDepressed)
                    {
                        if (m_group.Count == 0)
                        {
                            Text.FontColor = Color.Black;
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.TriButtonCenterDown, ScreenFrame);
                        }

                        else
                        {
                            Text.FontColor = Color.White;
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.TriButtonCenterheightlight, ScreenFrame);
                        }
                    }

                    else
                    {
                            Text.FontColor = Color.Black;
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.TriButtonCenter, ScreenFrame);
                    }
                    break;

                case ToggleStyle.TriRight:
                    if (IsDepressed)
                    {
                        if (m_group.Count == 0)
                        {
                            Text.FontColor = Color.Black;
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.TriButtonRightDown, ScreenFrame);
                        }

                        else
                        {
                            Text.FontColor = Color.White;
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.TriButtonRightHighlight, ScreenFrame);
                        }
                    }

                    else
                    {
                            Text.FontColor = Color.Black;
                            Gui.Draw9SliceImage(GuiDrawer.StandardTextures.TriButtonRight, ScreenFrame);
                    }

                    break;
            }

            if (Image != null)
                Gui.DrawImage(Image, new Rectangle(ScreenFrame.X + 5, ScreenFrame.Y + 5, ScreenFrame.Width - 10, ScreenFrame.Height - 10));
            
        }

    }
}
