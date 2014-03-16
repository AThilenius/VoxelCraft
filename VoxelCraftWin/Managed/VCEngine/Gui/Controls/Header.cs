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

        public Header()
        {
            DragBegin += (s, a) => m_delta = GlfwInputState.InvertedMouseLocation;
            Draging += Header_Draging;

            HudOverlay = new Hud();
            AddControl(HudOverlay);

            PagesPicker = new MainPagesPicker();
            AddControl(PagesPicker);
        }

        void Header_Draging(object sender, MouseEventArgs e)
        {
            Editor.MainWindow.Position = Editor.MainWindow.Position + (GlfwInputState.InvertedMouseLocation - m_delta);
            GlfwInputState.InvertedMouseLocation = m_delta;
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            Gui.DrawButton(sf);
            Gui.DrawImage(@"Icons\RoundButton.DDS", new Rectangle(sf.X + 30, sf.Y + 15, 45, 45));
            Gui.DrawImage(@"Icons\Play.DDS", new Rectangle(sf.X + 45, sf.Y + 27, 20, 20));

            HudOverlay.ScreenFrame = new Rectangle(MathHelper.RoundedDevision(Editor.MainWindow.ScaledSize.X, 2) - 225, sf.Y + 5, 450, 65);
            PagesPicker.Location = new Point(Frame.Width - 400, MathHelper.RoundedDevision(Height, 2) - MathHelper.RoundedDevision(PagesPicker.Height, 2));

            if (PanelsButtons != null)
                PanelsButtons.Location = new Point(Frame.Width - 120, MathHelper.RoundedDevision(Height, 2) - MathHelper.RoundedDevision(PanelsButtons.Height, 2));
        }


    }
}