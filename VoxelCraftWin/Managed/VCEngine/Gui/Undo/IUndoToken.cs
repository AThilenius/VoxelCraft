﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public interface IUndoToken
    {
        void UndoToken();
        void ReDoToken();
    }
}
