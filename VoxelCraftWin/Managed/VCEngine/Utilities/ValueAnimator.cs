using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ValueAnimator<T> where T : IAnimatable
    {
        public enum InterpolationType
        {
            Linear,
            Triginometric
        }

        public float AnimationTime;
        public InterpolationType Interpolation = InterpolationType.Triginometric;

        public event EventHandler OnCompleation = delegate { };

        private float m_startTime;
        private float m_finishTime;
        private bool m_isAnimatin;
        private bool m_completionTriggered;
        private T m_from;
        private T m_to;

        public ValueAnimator(T from)
        {
            m_from = from;
        }

        public ValueAnimator(T from, T to, float animationTime)
        {
            AnimationTime = animationTime;
            m_from = from;
            m_to = to;

            m_startTime = Time.TotalTime;
            m_finishTime = Time.TotalTime + AnimationTime;
            m_isAnimatin = true;
            Editor.ShouldRedraw(AnimationTime);
        }

        public T GetValue()
        {
            if (!m_isAnimatin)
                return m_from;

            float linear = (Time.TotalTime - m_startTime) / (m_finishTime - m_startTime);

            if (linear < 0.0f)
                return m_from;

            if (linear > 1.0f)
            {
                if (!m_completionTriggered)
                {
                    OnCompleation(this, EventArgs.Empty);
                    m_completionTriggered = true;
                }

                return m_to;
            }

            if (Interpolation == InterpolationType.Linear)
                return (T) m_from.Lerp(m_from, m_to, linear);

            else if (Interpolation == InterpolationType.Triginometric)
                // Formula (arctan(x - pi) + 1.2626272556) / (1.2626272556 * 2)
                return (T) m_from.Lerp(m_from, m_to, (float)((Math.Atan(linear * 2.0f * Math.PI - Math.PI) + 1.2626272556f) / (1.2626272556f * 2.0f)));

            throw new Exception("Unsupported interpolation");
        }

    }
}
