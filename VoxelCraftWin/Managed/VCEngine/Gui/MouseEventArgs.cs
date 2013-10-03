using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public enum MouseEventType
    {
        Click,
        RightClick,
        DoubleClick,
        Move,
        DragBegin,
        Draging,
        DragEnd
    }

    public class MouseEventArgs : EventArgs
    {
        public Point ScreenLocation;
        public MouseEventType EventType;
    }
}
