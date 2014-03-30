using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Header : Control
    {
        public Hud HudOverlay;
        public MainPagesPicker PagesPicker;
        public PanelsTrippleButton PanelsButtons
        {
            get { return m_panelsButtons; }
            set
            {
                if (m_panelsButtons != null)
                {
                    m_panelsButtons.Visible = false;
                    RemoveControl(m_panelsButtons);
                }

                m_panelsButtons = value;
                m_panelsButtons.Visible = true;
                AddControl(m_panelsButtons);
            }
        }


        private Point m_delta = new Point(-1, -1);
        private PanelsTrippleButton m_panelsButtons;
        private Texture m_playIcon = Texture.Get(@"Icons\Play.DDS");

        public Header(Window window) : base(window)
        {
            HudOverlay = new Hud(ParentWindow);
            AddControl(HudOverlay);

            PagesPicker = new MainPagesPicker(ParentWindow);
            AddControl(PagesPicker);
        }

        void Header_Draging(object sender, MouseEventArgs e)
        {
            ParentWindow.Position = ParentWindow.Position + (m_glfwInputState.InvertedMouseLocation - m_delta);
            m_glfwInputState.InvertedMouseLocation = m_delta;
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            GuiDrawer.DrawButton(sf);
            GuiDrawer.DrawImage(Gui.StandardTextures.RoundButton, new Rectangle(sf.X + 30, sf.Y + 15, 45, 45));
            GuiDrawer.DrawImage(m_playIcon, new Rectangle(sf.X + 45, sf.Y + 27, 20, 20));

            HudOverlay.ScreenFrame = new Rectangle(MathHelper.RoundedDevision(ParentWindow.ScaledSize.X, 2) - 225, sf.Y + 5, 450, 65);
            PagesPicker.Location = new Point(Frame.Width - 400, MathHelper.RoundedDevision(Height, 2) - MathHelper.RoundedDevision(PagesPicker.Height, 2));

            if (PanelsButtons != null)
                PanelsButtons.Location = new Point(Frame.Width - 120, MathHelper.RoundedDevision(Height, 2) - MathHelper.RoundedDevision(PanelsButtons.Height, 2));
        }


    }
}