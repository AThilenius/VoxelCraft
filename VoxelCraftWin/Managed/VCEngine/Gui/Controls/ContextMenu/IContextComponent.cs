using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public interface IContextComponent
    {
        event EventHandler OnExpand;
        event EventHandler OnCollapse;
        Boolean HasHeader { get; }
        Boolean IsExpanded { get; }
        Control Header { get; }
        Control Body { get; }
    }
}
