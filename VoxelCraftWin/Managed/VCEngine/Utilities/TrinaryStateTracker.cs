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

                case TriState.Pressed:
                    if (value)
                        m_state = TriState.Replete;
                    else
                        m_state = TriState.Up;
                    break;

                case TriState.Replete:
                    if (!value)
                        m_state = TriState.Up;
                    break;

                case TriState.Up:
                    if (value)
                        m_state = TriState.Pressed;
                    else
                        m_state = TriState.None;
                    break;
            }

        }

    }
}
