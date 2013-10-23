using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Control
    {
        // static (Used by main control only)
        public static Control MainControl = null;
        private static HashSet<Control> s_currentFocus = new HashSet<Control>();
        private static HashSet<Control> s_lastFocus = new HashSet<Control>();
        private static Control m_focusedChild;

        // Appearance
        public String       Name;
        public Rectangle    Frame
        {
            get { return m_frame; }
            set
            {
                ResizeEventArgs args = new ResizeEventArgs { From = m_frame, To = value };
                m_frame = value;
                Resize(this, args);
            }
        }
        public int          BorderWidth;

        public Color        BackgroundColor = Color.ControlMediumBackground;
        public Color        BorderColor = Color.ControlVeryDark;

        public bool         DrawHover;
        public Color        HoverBackgroundColor = Color.White;
        public Color        HoverBorderColor = Color.ControlBorder;

        public String       Font = "Calibri-16";

        // Control
        public Control Parent;
        public bool Enabled = true;
        public bool Visible = true;
        public bool CanFocus;
        public HashSet<Control> Children = new HashSet<Control>();
        public bool IsFocused;
        public bool IsHovered { get; protected set; }
        public bool IsClickDown { get; protected set; }

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

        public event EventHandler<MouseEventArgs> Click = delegate { };
        public event EventHandler<MouseEventArgs> RightClick = delegate { };
        public event EventHandler<MouseEventArgs> DoubleClick = delegate { };
        public event EventHandler MouseEnter = delegate { };
        public event EventHandler MouseExit = delegate { };
        public event EventHandler<MouseEventArgs> MouseMove = delegate { };
        public event EventHandler<MouseEventArgs> DragBegin = delegate { };
        public event EventHandler<MouseEventArgs> DragEnd = delegate { };
        public event EventHandler<MouseEventArgs> Draging = delegate { };
        public event EventHandler<KeyEventArgs> KeyPress = delegate { };
        public event EventHandler<CharEventArgs> CharPress = delegate { };
        public event EventHandler<ControlFocusArgs> Focused = delegate { };
        public event EventHandler<ResizeEventArgs> Resize = delegate { };
        public event EventHandler<ParentChangeEventArgs> ParentChanged = delegate { };

        private Rectangle m_frame = new Rectangle();
        private Control m_activeChild;
        private bool m_wasPointInThis;

        public Control()
        {
            MouseEnter += (s, a) => { IsHovered = true; IsClickDown = false; };
            MouseExit += (s, a) => { IsHovered = false;  IsClickDown = false; };
        }

        // Called externally
        public void Render()
        {
            Draw();

            foreach (Control ctrl in Children)
                if (ctrl.Visible)
                    ctrl.Render();
        }

        public virtual void AddControl(Control control)
        {
            Children.Add(control);

            if (control.Parent != null)
                control.Parent.RemoveControl(control);

            ParentChangeEventArgs args = new ParentChangeEventArgs { OldParent = control.Parent, NewParent = this };
            control.Parent = this;
            control.ParentChanged(this, args);
        }

        public virtual void RemoveControl(Control control)
        {
            Children.Remove(control);
            ParentChangeEventArgs args = new ParentChangeEventArgs { OldParent = control.Parent, NewParent = null };
            control.Parent = null;
            control.ParentChanged(this, args);
        }

        protected virtual void Draw()
        {
            if (IsFocused)
            {
                if (HoverBackgroundColor != Color.Trasparent)
                    Gui.DrawRectangle(ScreenFrame, HoverBackgroundColor);

                if (BorderWidth > 0)
                    Gui.DrawBorderedRect(ScreenFrame, Color.Trasparent, Color.ControlBlue, BorderWidth);
            }
            else
            {
                if (IsHovered && DrawHover && Enabled)
                {
                    if (HoverBackgroundColor != Color.Trasparent)
                        Gui.DrawRectangle(ScreenFrame, HoverBackgroundColor);

                    if (BorderWidth > 0)
                        Gui.DrawBorderedRect(ScreenFrame, Color.Trasparent, HoverBorderColor, BorderWidth);
                }

                else
                {
                    if (BackgroundColor != Color.Trasparent)
                        Gui.DrawRectangle(ScreenFrame, BackgroundColor);

                    if (BorderWidth > 0)
                        Gui.DrawBorderedRect(ScreenFrame, Color.Trasparent, BorderColor, BorderWidth);
                }
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
            if (!Enabled)
                return false;

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
            Window.Resize += (sender, args) =>
                {
                    MainControl.Frame = args.To;
                };

            Input.KeyClicked += ((sender, args) =>
                {
                    if (m_focusedChild != null)
                        m_focusedChild.ProcessKeyEvent(this, new KeyEventArgs { State = args.State });
                });

            Input.CharClicked += (sender, args) =>
                {
                    if (m_focusedChild != null)
                        m_focusedChild.CharPress(sender, args);
                };

            Input.MouseClick += ((sender, args) =>
                {
                    // Rebuild command chain
                    RebuildCommandChain(args.ScreenLocation);

                    Control active = GetEndOfCommandChain();


                    if (args.Action == TriState.Pressed)
                    {
                        active.IsClickDown = true;
                        m_focusedChild = null;

                        // Walk up the chain, set focus flags
                        Control cursor = active;
                        while (cursor.Parent != null)
                        {
                            if (cursor.CanFocus)
                            {
                                if (m_focusedChild == null)
                                    m_focusedChild = cursor;

                                s_currentFocus.Add(cursor);

                                if (!cursor.IsFocused)
                                {
                                    cursor.IsFocused = true;
                                    cursor.Focused(this, new ControlFocusArgs { IsFocused = true });
                                }
                            }

                            cursor = cursor.Parent;
                        }

                        // UnFocus any control not touched while walking
                        foreach (Control ctrl in s_lastFocus)
                        {
                            if (!s_currentFocus.Contains(ctrl))
                            {
                                ctrl.IsFocused = false;
                                ctrl.Focused(this, new ControlFocusArgs { IsFocused = false });
                            }
                        }

                        s_lastFocus = s_currentFocus;
                        s_currentFocus = new HashSet<Control>();
                    }

                    else if (args.Action == TriState.Up)
                    {
                        // Forward event for further processing
                        active.ProcessMouseEvent(
                            this,
                            new MouseEventArgs
                            {
                                EventType = args.Button == MouseClickEventArgs.MouseButton.Left ? MouseEventType.Click : MouseEventType.RightClick,
                                ScreenLocation = args.ScreenLocation
                            }
                        );

                        active.IsClickDown = false;
                    }
                });

            Input.MouseMove += ((sender, args) =>
                {
                    // Rebuild command chain
                    RebuildCommandChain(args.ScreenLocation);
                    Control active = GetEndOfCommandChain();

                    if (m_activeChild == null)
                        Input.ActivateUpdates();
                    else
                        Input.SuppressUpdates();

                    if (active.IsClickDown)
                    {
                        active.ProcessMouseEvent(
                            this,
                            new MouseEventArgs
                            {
                                EventType = MouseEventType.Draging,
                                ScreenLocation = args.ScreenLocation
                            }
                        );
                    }

                    else
                    {
                        active.ProcessMouseEvent(
                            this,
                            new MouseEventArgs
                            {
                                EventType = MouseEventType.Move,
                                ScreenLocation = args.ScreenLocation
                            }
                        );
                    }
                });

            Input.Focus += ((sender, args) =>
                {
                    // Rebuild command chain
                    RebuildCommandChain(new Point(-1, -1));

                    if (m_activeChild == null)
                        Input.ActivateUpdates();
                    else
                        Input.SuppressUpdates();
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
