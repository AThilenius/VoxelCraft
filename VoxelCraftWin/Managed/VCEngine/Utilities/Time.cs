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
        public static float DeltaTime = 0.1f;
        public static float CurrentTime { get { return (float)m_stopwatch.ElapsedMilliseconds * 0.001f; } }

        private static Stopwatch m_stopwatch = new Stopwatch();

        static Time()
        {
            m_stopwatch.Start();
        }

        internal static void Update()
        {
            float newTime = (float)m_stopwatch.ElapsedMilliseconds * 0.001f;
            DeltaTime = newTime - TotalTime;
            TotalTime = newTime;
        }

    }
}
