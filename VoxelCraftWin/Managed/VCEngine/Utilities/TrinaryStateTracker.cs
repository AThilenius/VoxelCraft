using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public enum TriState
    {
        None,
        Pressed,
        Replete,
        Up
    }

    public struct TrinaryStateTracker
    {
        private TriState m_state;
        public TriState State { get { return m_state; } }

        public void Update(bool value)
        {

            switch (State)
            {
                case TriState.None:
                    if (value)
                        m_state = TriState.Pressed;
                    break;

                case TriState.Replete:
                    if (!value)
                        m_state = TriState.Up;
                    break;
            }

        }

        public void StepState()
        {

            switch (State)
            {
                case TriState.Pressed:
                    m_state = TriState.Replete;
                    break;

                case TriState.Up:
                    m_state = TriState.None;
                    break;
            }

        }

    }
}
