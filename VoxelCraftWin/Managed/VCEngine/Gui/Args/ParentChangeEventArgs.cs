using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ParentChangeEventArgs : EventArgs
    {
        public Control OldParent;
        public Control NewParent;
    }
}
