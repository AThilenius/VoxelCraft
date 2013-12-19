using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public interface IAnimatable
    {
        IAnimatable Lerp(IAnimatable from, IAnimatable to, float ammount);
    }
}
