using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Header : Control
    {
        public LayoutControls LayoutControls;
        public Hud HudOverlay;
        public PanelsControler Panels;
        public MainPagesPicker PagesPicker;

        private Point m_delta = new Point(-1, -1);

        public Header()
        {
            DragBegin += (s, a) => m_delta = GlfwInputState.InvertedMouseLocation;
            Draging += Header_Draging;

            HudOverlay = new Hud();
            AddControl(HudOverlay);

            Panels = new PanelsControler();
            AddControl(Panels);

            PagesPicker = new MainPagesPicker();
            AddControl(PagesPicker);
        }

        void Header_Draging(object sender, MouseEventArgs e)
        {
            Window.Position = Window.Position + (GlfwInputState.InvertedMouseLocation - m_delta);
            GlfwInputState.InvertedMouseLocation = m_delta;
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            Gui.DrawButton(sf);
            Gui.DrawImage(@"Icons\RoundButton.DDS", new Rectangle(sf.X + 30, sf.Y + 15, 45, 45));
            Gui.DrawImage(@"Icons\Play.DDS", new Rectangle(sf.X + 45, sf.Y + 27, 20, 20));

            HudOverlay.ScreenFrame = new Rectangle(MathHelper.RoundedDevision(Window.ScaledSize.X, 2) - 225, sf.Y + 5, 450, 65);
            Panels.Location = new Point(Frame.Width - 120, MathHelper.RoundedDevision(Height, 2) - MathHelper.RoundedDevision(Panels.Height, 2));
            PagesPicker.Location = new Point(Frame.Width - 400, MathHelper.RoundedDevision(Height, 2) - MathHelper.RoundedDevision(Panels.Height, 2));
            
        }


    }
}