using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public interface IInteropOutCallbacks
    {
        // Invoked as:
        // RETURNTYPE Invoke##FNAME ARGS

        //void InvokeRendererRender(int from);
    }

    public class InteropOut
    {
        public static IInteropOutCallbacks Callbacks;

        public static void SetCallbacks(IInteropOutCallbacks callbacks)
        {
            Callbacks = callbacks;
        }

    }
}
