using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public static class Time
    {
        public static float TotalTime;
        public static TimeSpan TotalTimespan = new TimeSpan();
        public static float DeltaTime = 0.1f;
        public static TimeSpan DeltaTimeSpan = new TimeSpan(0, 0, 0, 0, 100);
        //public static float CurrentTime { get { return (float)m_stopwatch.ElapsedMilliseconds * 0.001f; } }

        private static Stopwatch m_stopwatch = new Stopwatch();
        private static TimeSpan m_lastTime = new TimeSpan();

        static Time()
        {
            m_stopwatch.Start();
        }

        internal static void Update()
        {
            TotalTimespan = m_stopwatch.Elapsed;
            DeltaTimeSpan = TotalTimespan - m_lastTime;
            TotalTime = (float) DeltaTimeSpan.TotalSeconds;
        }


        internal static void Pause()
        {
            m_stopwatch.Stop();
        }

        internal static void Resume()
        {
            m_stopwatch.Start();
        }
    }
}
