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
        public static float CurrentTime { get { return (float)m_stopwatch.ElapsedMilliseconds * 0.001f; } }

        private static Stopwatch m_stopwatch = new Stopwatch();

        static Time()
        {
            m_stopwatch.Start();
        }

        internal static void Update()
        {
            TotalTimespan = m_stopwatch.Elapsed;
            float newTime = (float)TotalTimespan.TotalSeconds;
            DeltaTime = newTime - TotalTime;
            TotalTime = newTime;
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
