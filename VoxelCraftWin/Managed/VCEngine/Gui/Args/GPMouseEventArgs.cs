using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class GPMouseEventArgs : EventArgs
    {
        public TriState[] ButtonStates = new TriState[10];
        public Point MousePoistion;
        public Point DeltaLook;
    }
}
