using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Control
    {
        public static Control MainControl;

        public String Name;
        public Rectangle Frame = new Rectangle();
        public Control Parent;
        public Color BackgroundColor = Color.ControlLight;
        public int BorderWidth = 0;
        public Color BorderColor = Color.ControlVeryDark;
        public Color HighlightBackgroundColor = Color.White;
        public Color HightlightBorderColor = Color.ControlBorder;
        public bool Enabled = true;
        public bool Visible = true;
        public String Font = "Lucida Sans-13-Bold";
        public HashSet<Control> Children = new HashSet<Control>();
        public bool IsHovered { get; protected set; }

        public Point ScreenPoint
        {
            get
            {
                if (Parent == null)
                    return new Point(Frame.X, Frame.Y);

                else
                {
                    // Recursive
                    return Parent.ScreenPoint + new Point(Frame.X, Frame.Y);
                }
            }

            set
            {
                if (Parent == null)
                    Frame = new Rectangle(value.X, value.Y, Frame.Width, Frame.Height);

                else
                {
                    // Recursive
                    Point p = new Point(Frame.X, Frame.Y) - Parent.ScreenPoint;
                    Frame = new Rectangle(p, Frame.Width, Frame.Height);
                }
            }
        }
        public Rectangle ScreenFrame
        {
            get
            {
                return new Rectangle(ScreenPoint, Frame.Width, Frame.Height);
            }

            set
            {
                if (Parent == null)
                    Frame = new Rectangle(value.X, value.Y, value.Width, value.Height);

                else
                {
                    Point p = new Point(value.X, value.Y) - Parent.ScreenPoint;
                    Frame = new Rectangle(p, value.Width, value.Height);
                }
            }
        }

        public event EventHandler Click = delegate { };
        public event EventHandler RightClick = delegate { };
        public event EventHandler DoubleClick = delegate { };
        public event EventHandler MouseEnter = delegate { };
        public event EventHandler MouseExit = delegate { };
        public event EventHandler MouseMove = delegate { };
        public event EventHandler<MouseEventArgs> DragBegin = delegate { };
        public event EventHandler<MouseEventArgs> DragEnd = delegate { };
        public event EventHandler<MouseEventArgs> Draging = delegate { };
        public event EventHandler<KeyEventArgs> KeyPress = delegate { };

        private Control m_activeChild;
        private bool m_wasPointInThis;

        public Control()
        {
            MouseEnter += (s, a) => IsHovered = true;
            MouseExit += (s, a) => IsHovered = false;
        }

        // Called externally
        public void Render()
        {
            Draw();

            foreach (Control ctrl in Children)
                if (ctrl.Visible)
                    ctrl.Render();
        }

        public void AddControl(Control control)
        {
            Children.Add(control);
            control.Parent = this;
        }

        public void RemoveControl(Control control)
        {
            Children.Remove(control);
            control.Parent = null;
        }

        protected virtual void Draw()
        {
            if (IsHovered)
            {
                if (BorderWidth > 0)
                    Gui.DrawBorderedRect(ScreenFrame, Color.Trasparent, HightlightBorderColor, BorderWidth);

                if (HighlightBackgroundColor != Color.Trasparent)
                    Gui.DrawRectangle(ScreenFrame, HighlightBackgroundColor);
            }

            else
            {
                if (BorderWidth > 0)
                    Gui.DrawBorderedRect(ScreenFrame, Color.Trasparent, BorderColor, BorderWidth);

                if (BackgroundColor != Color.Trasparent)
                    Gui.DrawRectangle(ScreenFrame, BackgroundColor);
            }
        }

        internal bool ProcessKeyEvent(Object sender, KeyEventArgs args)
        {
            if (KeyPress != null)
            {
                KeyPress(sender, args);
                return true;
            }
            return false;
        }

        internal bool ProcessMouseEvent(Object sender, MouseEventArgs args)
        {
            // Fire event handler if there is one. Return false if not.
            switch (args.EventType)
            {
                case MouseEventType.Click:
                    if (Click != null)
                    {
                        Click(sender, args);
                        return true;
                    }
                    return false;

                case MouseEventType.RightClick:
                    if (RightClick != null)
                    {
                        RightClick(sender, args);
                        return true;
                    }
                    return false;

                case MouseEventType.DoubleClick:
                    if (DoubleClick != null)
                    {
                        DoubleClick(sender, args);
                        return true;
                    }
                    return false;

                case MouseEventType.Move:
                    if (MouseMove != null)
                    {
                        MouseMove(sender, args);
                        return true;
                    }
                    return false;

                case MouseEventType.DragBegin:
                    if (DragBegin != null)
                    {
                        DragBegin(sender, args);
                        return true;
                    }
                    return false;

                case MouseEventType.DragEnd:
                    if (DragEnd != null)
                    {
                        DragEnd(sender, args);
                        return true;
                    }
                    return false;

                case MouseEventType.Draging:
                    if (Draging != null)
                    {
                        Draging(sender, args);
                        return true;
                    }
                    return false;

                default:
                    Console.WriteLine("Unknown mouse event type.");
                    return false;
            }
        }

        internal void SetFirstResponder()
        {
            Input.KeyClicked += ((sender, args) =>
                {
                    GetEndOfCommandChain().ProcessKeyEvent(
                        this,
                        new KeyEventArgs { State = args.State }
                    );
                });

            Input.MouseClick += ((sender, args) =>
                {
                    GetEndOfCommandChain().ProcessMouseEvent(
                        this,
                        new MouseEventArgs
                        {
                            EventType = MouseEventType.Click,
                            ScreenLocation = args.ScreenLocation
                        }
                    );
                });

            Input.MouseMove += ((sender, args) =>
                {
                    // Rebuild command chain
                    RebuildCommandChain(args.ScreenLocation);

                    GetEndOfCommandChain().ProcessMouseEvent(
                        this, 
                        new MouseEventArgs { 
                            EventType = MouseEventType.Move, 
                            ScreenLocation = args.ScreenLocation }
                    );
                });

            Input.Focus += ((sender, args) =>
                {
                    // Rebuild command chain
                    RebuildCommandChain(new Point(-1, -1));
                });
        }

        private void RebuildCommandChain(Point point)
        {
            if (Visible && !m_wasPointInThis && ScreenFrame.IsPointWithin(point))
            {
                MouseEnter(this, EventArgs.Empty);
                m_wasPointInThis = true;
            }

            // If its in a child's frame...
            foreach (Control child in Children)
            {
                if (child.Visible && child.ScreenFrame.IsPointWithin(point))
                {
                    if (m_activeChild != null && m_activeChild != child)
                    {
                        //m_activeChild.RebuildCommandChain(point);
                        Control ctrl = m_activeChild;
                        while (ctrl != null)
                        {
                            ctrl.MouseExit(this, EventArgs.Empty);
                            ctrl.m_wasPointInThis = false;
                            ctrl = ctrl.m_activeChild;
                        }
                    }

                    m_activeChild = child;
                    child.RebuildCommandChain(point);

                    return;
                }
            }

            // Its in our frame, not a child's
            if (m_activeChild != null)
            {
                //m_activeChild.RebuildCommandChain(point);
                Control ctrl = m_activeChild;
                while (ctrl != null)
                {
                    ctrl.MouseExit(this, EventArgs.Empty);
                    ctrl.m_wasPointInThis = false;
                    ctrl = ctrl.m_activeChild;
                }
                m_activeChild = null;
            }
        }

        private Control GetEndOfCommandChain()
        {
            if (m_activeChild == null)
                return this;

            return m_activeChild.GetEndOfCommandChain();
        }

    }
}
