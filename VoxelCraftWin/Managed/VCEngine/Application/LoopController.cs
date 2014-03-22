using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;

namespace VCEngine
{
    public static class LoopController
    {

        public static event EventHandler OnLoop = delegate { };

        public static Boolean ShouldLoop = true;
        public static Boolean ThrotteledUpdate = false;
        public static int DesiredFPS
        {
            get { return (int)Math.Round(m_desiredFrameTime * 60.0d); }
            set { m_desiredFrameTime = 1.0d / ((Double)value); }
        }
        public static Boolean Paused = false;

        private static Stopwatch m_loopTimer = new Stopwatch();
        private static double m_lastFrameTime;
        private static double m_desiredFrameTime = 0.016666666666d;

        public static void PassControlAndBegin()
        {
            m_loopTimer.Start();

            while (ShouldLoop)
            {
                Double currentTime = (Double) m_loopTimer.ElapsedMilliseconds / 1000.0d;
                Double deltaTime = currentTime - m_lastFrameTime;
                
                // If last frame is within 1/60th of a second, then sleep for 1/60 - Delta
                if (ThrotteledUpdate && deltaTime < m_desiredFrameTime)
                {
                    int desiredSleepMs = (int) Math.Floor((m_desiredFrameTime - deltaTime) * 1000.0d);
                    int maxMs = (int)(m_desiredFrameTime * 1000.0d);
                    Thread.Sleep(MathHelper.Clamp(desiredSleepMs, 0, maxMs));
                }

                m_lastFrameTime = currentTime;

                if (!Paused)
                {
                    VCEngineCore.PropagateUpdates();
                    OnLoop(null, EventArgs.Empty);

                    // Need to quit?
                    if (Window.ActiveWindows.Count == 0)
                        return;
                }
            }
        }

        #region Console Commands

        [ConsoleFunction("Boolean flag for update throttling", "Update")]
        public static String ThrottleUpdate(String[] args)
        {
            ThrotteledUpdate = Boolean.Parse(args[1]);
            return "";
        }

        [ConsoleFunction("Get the set FPS limit of the update loop", "Update")]
        public static String GetFPS(String[] args)
        {
            return DesiredFPS.ToString("12.34") + " FPS.";
        }

        [ConsoleFunction("Sets the FPS limit of the update loop", "Update")]
        public static String SetFPS(String[] args)
        {
            DesiredFPS = Int32.Parse(args[1]);
            return "";
        }

        [ConsoleFunction("Pause all updating", "Update")]
        public static String Pause(String[] args)
        {
            Paused = true;
            return "";
        }

        [ConsoleFunction("Pause all updating", "Update")]
        public static String Resume(String[] args)
        {
            Paused = false;
            return "";
        }

        #endregion


    }
}
