using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace VCEngine
{
    public enum DelayInvokeOrder : int
    {
        PreSetup = 0,
        PreDefault = 1,
        Default = 2,
        PostDefault = 3
    }

    [System.AttributeUsage(AttributeTargets.Method)]
    public class DelayedInvoke : System.Attribute
    {
        public DelayInvokeOrder InvokeOrder;

        public DelayedInvoke(DelayInvokeOrder invokeOrder = DelayInvokeOrder.Default)
        {
            this.InvokeOrder = invokeOrder;
        }
    }

    public static class DelayedInvokeHelper
    {
        public static void Invoke(DelayInvokeOrder invokeOrder)
        {
            // Inefficient, probably not a problem though.
            foreach (MethodInfo mInfo in Reflection.GetMethodsWithAttribute(Assembly.GetExecutingAssembly(), typeof(DelayedInvoke), BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Static))
            {
                DelayedInvoke invokeAttr = (DelayedInvoke)mInfo.GetCustomAttributes(typeof(DelayedInvoke), false)[0];

                if (invokeAttr.InvokeOrder == invokeOrder)
                    mInfo.Invoke(null, null);
            }
        }

    }
}
