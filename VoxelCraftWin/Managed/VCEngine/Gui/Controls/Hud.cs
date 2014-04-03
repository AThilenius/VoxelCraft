using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Hud : Control
    {
        public Label HudLabel;
        public Double NotificationDelay = 2.0d;

        private int m_yOffset;
        private int m_frameCount;
        private Double m_lastLoopTime;
        private Double m_lastDrawTime;

        private Font m_fontConsolas;
        private Texture m_hudTexture = Texture.GetInResources(@"Images\Icons\Hud.DDS");

        private Queue<Label> m_notificationQueue = new Queue<Label>();
        private List<Label> m_displayQueue = new List<Label>();
        private Label m_activeNotification;
        private Double m_nextNotifyTime;

        public Hud(Window window) : base(window)
        {
            HudLabel = new Label(ParentWindow, "VoxelCraft Beta 0.0.1 Thilenius");
            AddControl(HudLabel);
            HudLabel.Font = VCEngine.Font.GetFont(HudLabel.Font.Name, 16, ParentWindow, true);
            m_fontConsolas = Font.GetFont("Consolas", 12, ParentWindow);

            // Listen for Notifications from the log
            Log.OnNotify += (s, a) => 
                {
                    if (m_notificationQueue.Where(item => item.Text == a.Message).Count() == 0)
                    {
                        Label notification = new Label(window, a.Message);
                        AddControl(notification);
                        notification.Frame = new Rectangle(10, 0, 450 - 20, 10);
                        notification.FontColor = Color.Trasparent;
                        m_notificationQueue.Enqueue(notification);
                    }
                };
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            Gui.Draw9SliceImage(m_hudTexture, sf, 10, 0.17f);
            HudLabel.Frame = new Rectangle(0, Height - 20, Width, HudLabel.Height);

            // Smooth out FPS values
            //m_lastLoopTime = m_lastLoopTime * 0.99d + ParentWindow.LastLoopTime.TotalSeconds * 0.01d;
            //m_lastDrawTime = m_lastDrawTime * 0.99d + ParentWindow.LastDrawTime.TotalSeconds * 0.01d;

            //m_yOffset = 35;
            //DrawText("        Full Loop FPS: [ " + (1.0d / m_lastLoopTime).ToString("0000") + " ]", sf);
            //DrawText("           OpenGL FPS: [ " + (1.0d / m_lastDrawTime).ToString("0000") + " ]", sf);
            //DrawText("   Drawn Frames Count: [ " + m_frameCount++ + " ]", sf);

            //m_yOffset = 35;
            //DrawText("           Resolution: " + ParentWindow.TrueSize, sf, 220);
            //DrawText("Gui Scaled Resolution: " + ParentWindow.ScaledSize, sf, 220);
            //DrawText("                Mouse: " + m_glfwInputState.MouseLocation, sf, 220);

            // Offsets:
            // NAN:     +40
            // Active:  +30
            // - 1:     +20
            // - 2:     +10

            if ((m_notificationQueue.Count > 0 || m_displayQueue.Count > 0 || m_activeNotification != null)
                && m_nextNotifyTime < Time.CurrentTime)
            {
                m_nextNotifyTime = Time.CurrentTime + NotificationDelay;

                if (m_activeNotification != null)
                {
                    Label active = m_activeNotification;

                    // Animate into deletion
                    m_activeNotification.AnimateLocation(new Point(10, 40), () => RemoveControl(active));
                    m_activeNotification.AnimateFontColor(Color.Trasparent);
                    m_activeNotification = null;
                }

                // Make sure all or at most 3 notifications are in display Queue
                while (m_displayQueue.Count < 3 && m_notificationQueue.Count > 0)
                {
                    Label label = m_notificationQueue.Dequeue();
                    label.Visible = true;
                    m_displayQueue.Insert(m_displayQueue.Count, label);
                }

                // Set active if there is more than one in the display Queue
                if (m_displayQueue.Count > 0)
                {
                    m_activeNotification = m_displayQueue[0];
                    m_activeNotification.AnimateLocation(new Point(10, 30));
                    m_activeNotification.AnimateFontColor(Color.Black);
                    m_displayQueue.RemoveAt(0);
                }

                // Animate the rest of the display Queue
                if (m_displayQueue.Count >= 1)
                {
                    m_displayQueue[0].AnimateLocation(new Point(10, 20));
                    m_displayQueue[0].AnimateFontColor(new Color(0, 0, 0, 180));
                }

                if (m_displayQueue.Count >= 2)
                {
                    m_displayQueue[1].AnimateLocation(new Point(10, 10));
                    m_displayQueue[1].AnimateFontColor(new Color(0, 0, 0, 40));
                }
            }

        }

        private void DrawText(string text, Rectangle sf, int xOffset = 0)
        {
            m_fontConsolas.DrawStringBeveled(text, new Point(sf.X + 5 + xOffset, sf.Y + sf.Height - m_yOffset), Color.Black);
            m_yOffset += 10;
        }
    }
}
