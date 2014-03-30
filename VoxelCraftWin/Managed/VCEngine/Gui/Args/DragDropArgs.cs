using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// Provided to the control who began the dragging. Fill in the Message slot.
    /// </summary>
    public class DragBeginArgs : EventArgs
    {
        public Object Message = null;
    }

    /// <summary>
    /// Sent to the TARGET control when an item is dropped upon it.
    /// </summary>
    public class DragDropArgs : EventArgs
    {
        public Control Sender;
        public Object Message;
        public Point Origin;
        public MouseEventArgs MouseArgs;

        public DragDropArgs(Control sender, Object message, Point origin, MouseEventArgs mouseArgs)
        {
            Sender = sender;
            Message = message;
            Origin = origin;
            MouseArgs = mouseArgs;
        }

    }
}
