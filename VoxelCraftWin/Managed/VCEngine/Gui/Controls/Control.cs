﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Control
    {
        // =====   Enums / Flags / Structs   =====================================
        public enum Dockings
        {
            None,
            Left,
            Right,
            Top,
            Bottom,
            Fill
        }

        [Flags]
        public enum Ancors
        {
            None = 0,
            Left = 1,
            Right = 2,
            Top = 4,
            Bottom = 8
        }

        public enum AutoSizeTypes
        {
            None,
            GrowOnly,
            GrowAndShrink
        }

        public struct MarginSize
        {
            public int Left;
            public int Right;
            public int Top;
            public int Bottom;

            public MarginSize(int left, int right, int top, int bottom)
            {
                Left = left;
                Right = right;
                Top = top;
                Bottom = bottom;
            }
        }

        // =====   Statics (Used by main control only)   =========================
        public static Control MainControl = null;
        private static HashSet<Control> s_currentFocus = new HashSet<Control>();
        private static HashSet<Control> s_lastFocus = new HashSet<Control>();
        private static Control s_focusedChild;

        // =====   Appearance   ==================================================
        public String           Name;
        public Rectangle        Frame
        {
            get { return m_frame; }
            set
            {
                ResizeEventArgs args = new ResizeEventArgs { From = m_frame, To = value };
                m_frame = value;
                
                // Update THIS Dock (Recursive downward) if this isn't master control.
                // Take the docked area from the Parent's remaining area to allow docking priorities
                if (Parent != null)
                {
                    // ===  Horizontal  ==========================================================

                    if (Dock == Dockings.Left)
                    {
                        m_frame.X = Parent.m_remainingDockFrame.X;
                        m_frame.Width = MathHelper.Clamp(m_frame.Width, 0, Parent.m_remainingDockFrame.Width);
                        m_frame.Y = Parent.m_remainingDockFrame.Y;
                        m_frame.Height = Parent.m_remainingDockFrame.Height;

                        Parent.m_remainingDockFrame.X += m_frame.Width + Margin.Right;
                        Parent.m_remainingDockFrame.Width -= m_frame.Width + Margin.Right;
                    }

                    else if (Dock == Dockings.Right)
                    {
                        m_frame.Width = MathHelper.Clamp(m_frame.Width, 0, Parent.m_remainingDockFrame.Width);
                        m_frame.X = MathHelper.Clamp(
                            Parent.m_remainingDockFrame.X + Parent.m_remainingDockFrame.Width - m_frame.Width,
                            Parent.m_remainingDockFrame.X,
                            Parent.m_remainingDockFrame.X + Parent.m_remainingDockFrame.Width);
                        m_frame.Y = Parent.m_remainingDockFrame.Y;
                        m_frame.Height = Parent.m_remainingDockFrame.Height;

                        Parent.m_remainingDockFrame.Width -= m_frame.Width + Margin.Right;
                    }

                    else if (Dock == Dockings.Bottom)
                    {
                        m_frame.Y = Parent.m_remainingDockFrame.Y;
                        m_frame.Height = MathHelper.Clamp(m_frame.Height, 0, Parent.m_remainingDockFrame.Height);
                        m_frame.X = Parent.m_remainingDockFrame.X;
                        m_frame.Width = Parent.m_remainingDockFrame.Width;

                        Parent.m_remainingDockFrame.Y += m_frame.Height + Margin.Bottom;
                        Parent.m_remainingDockFrame.Height -= m_frame.Height + Margin.Bottom;
                    }

                    else if (Dock == Dockings.Top)
                    {
                        m_frame.Height = MathHelper.Clamp(m_frame.Height, 0, Parent.m_remainingDockFrame.Height);
                        m_frame.Y = MathHelper.Clamp(
                            Parent.m_remainingDockFrame.Y + Parent.m_remainingDockFrame.Height - m_frame.Height,
                            Parent.m_remainingDockFrame.Y,
                            Parent.m_remainingDockFrame.Y + Parent.m_remainingDockFrame.Height);
                        m_frame.X = Parent.m_remainingDockFrame.X;
                        m_frame.Width = Parent.m_remainingDockFrame.Width;

                        Parent.m_remainingDockFrame.Height -= m_frame.Height + Margin.Bottom;
                    }

                    else if (Dock == Dockings.Fill)
                    {
                        m_frame = Parent.m_remainingDockFrame;
                        Parent.m_remainingDockFrame.Width = 0;
                        Parent.m_remainingDockFrame.Height = 0;
                    }

                }
                
                // Recursively update children docks in ascending order
                //m_remainingDockFrame = new Rectangle(Margin.Left, Margin.Bottom, m_frame.Width - (Margin.Left + Margin.Right), m_frame.Height - (Margin.Bottom + Margin.Top));
                m_remainingDockFrame = new Rectangle(0, 0, Frame.Width, Frame.Height);

                foreach (Control child in Children.OrderBy(ctrl => ctrl.DockOrder))
                    if (child.Dock != Dockings.None)
                        child.Frame = child.Frame;

                Resize(this, args);
            }
        }
        public Point            ScreenPoint
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
        public Rectangle        ScreenFrame
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
        public int              BorderWidth;
        public bool             ClipView;
        public int              DockOrder;
        public Dockings         Dock = Dockings.None;
        //public Anchors        AncorFlags = Ancors.None;
        public AutoSizeTypes    AutoSize = AutoSizeTypes.None;
        public MarginSize       Margin = new MarginSize();

        public Color            BackgroundColor = Color.ControlMediumBackground;
        public Color            BorderColor = Color.ControlVeryDark;

        public bool             DrawHover;
        public Color            HoverBackgroundColor = Color.White;
        public Color            HoverBorderColor = Color.ControlBorder;

        public Font             Font = Font.DefaultFont;

        // =====   Control   =====================================================
        public Control          Parent;
        public bool             Enabled = true;
        public bool             Visible = true;
        public bool             CanFocus;
        public HashSet<Control> Children = new HashSet<Control>();
        public bool             IsFocused;
        public bool             IsHovered { get; protected set; }
        public bool             IsClickDown { get; protected set; }
        public bool             IsRightClickDown { get; protected set; }
        public bool             IsDraging { get; private set; }


        // =====   Events   ======================================================
        public event EventHandler<MouseEventArgs>           Click = delegate { };
        public event EventHandler<MouseEventArgs>           RightClick = delegate { };
        public event EventHandler<MouseEventArgs>           DoubleClick = delegate { };
        public event EventHandler                           MouseEnter = delegate { };
        public event EventHandler                           MouseExit = delegate { };
        public event EventHandler<MouseClickEventArgs>      RawMouseClick = delegate { };
        public event EventHandler                           RawMouseMove = delegate { };
        public event EventHandler<KeyEventArgs>             RawKeyChange = delegate { };
        public event EventHandler<MouseEventArgs>           MouseMove = delegate { };
        public event EventHandler<MouseEventArgs>           DragBegin = delegate { };
        public event EventHandler<MouseEventArgs>           DragEnd = delegate { };
        public event EventHandler<MouseEventArgs>           Draging = delegate { };
        public event EventHandler<CharEventArgs>            CharPress = delegate { };
        public event EventHandler<ControlFocusArgs>         Focused = delegate { };
        public event EventHandler<ResizeEventArgs>          Resize = delegate { };
        public event EventHandler<ParentChangeEventArgs>    ParentChanged = delegate { };



        private Rectangle m_frame = new Rectangle();
        private Rectangle m_remainingDockFrame = new Rectangle();
        private Control m_activeChild;
        private bool m_wasPointInThis;
        private double m_lastClickTime;

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

        public void PropagateUpdate()
        {
            Update();

            foreach (Control ctrl in Children)
                ctrl.PropagateUpdate();
        }

        public virtual void AddControl(Control control)
        {
            Children.Add(control);

            if (control.Parent != null)
                control.Parent.RemoveControl(control);

            // Force an update
            Frame = Frame;
            
            ParentChangeEventArgs args = new ParentChangeEventArgs { OldParent = control.Parent, NewParent = this };
            control.Parent = this;
            control.ParentChanged(this, args);
        }

        public virtual void RemoveControl(Control control)
        {
            Children.Remove(control);

            //control.Resize -= ChildControlResizeHandler;
            //ChildControlResizeHandler(this, null);

            ParentChangeEventArgs args = new ParentChangeEventArgs { OldParent = control.Parent, NewParent = null };
            control.Parent = null;
            control.ParentChanged(this, args);
        }

        protected virtual void ChildControlResizeHandler(object sender, ResizeEventArgs e)
        {
            // Expand this control to contain all children
            if (AutoSize != AutoSizeTypes.None)
            {
                Rectangle size = new Rectangle();

                foreach (Control ctrl in Children)
                {
                    // Grow Up
                    if (ctrl.Frame.Y + ctrl.Frame.Height > size.Height)
                        size.Height = ctrl.Frame.Y + ctrl.Frame.Height + Margin.Top;

                    // Grow Right
                    if (ctrl.Frame.X + ctrl.Frame.Width > size.Width)
                        size.Width = ctrl.Frame.X + ctrl.Frame.Width;
                }

                if (AutoSize == AutoSizeTypes.GrowOnly)
                    Frame = new Rectangle(Frame.X, Frame.Y,
                        Math.Max(Frame.Width, size.Width),
                        Math.Max(Frame.Height, size.Height));

                if (AutoSize == AutoSizeTypes.GrowAndShrink)
                    Frame = new Rectangle(Frame.X, Frame.Y,
                        size.Width,
                        size.Height);

            }
        }

        protected virtual void Draw()
        {
            //if (IsFocused)
            //{
            //    if (HoverBackgroundColor != Color.Trasparent)
            //        Gui.DrawRectangle(ScreenFrame, HoverBackgroundColor);

            //    if (BorderWidth > 0)
            //        Gui.DrawBorderedRect(ScreenFrame, Color.Trasparent, Color.ControlBlue, BorderWidth);
            //}
            //else
            //{
            //    if (IsHovered && DrawHover && Enabled)
            //    {
            //        if (HoverBackgroundColor != Color.Trasparent)
            //            Gui.DrawRectangle(ScreenFrame, HoverBackgroundColor);

            //        if (BorderWidth > 0)
            //            Gui.DrawBorderedRect(ScreenFrame, Color.Trasparent, HoverBorderColor, BorderWidth);
            //    }

            //    else
            //    {
            //        if (BackgroundColor != Color.Trasparent)
            //            Gui.DrawRectangle(ScreenFrame, BackgroundColor);

            //        if (BorderWidth > 0)
            //            Gui.DrawBorderedRect(ScreenFrame, Color.Trasparent, BorderColor, BorderWidth);
            //    }
            //}
        }

        protected virtual void Update()
        {
        }

        private void UpdateFrame(Rectangle newFrame)
        {

        }
        
        internal void ProcessMouseEvent(Object sender, MouseEventArgs args)
        {
            if (!Enabled)
                return;

            // Fire event handler if there is one. Return false if not.
            switch (args.EventType)
            {
                case MouseEventType.Click:
                    Click(sender, args);

                    // 250ms double click
                    if (Time.CurrentTime < m_lastClickTime + 0.250f)
                        DoubleClick(sender, args);

                    m_lastClickTime = Time.CurrentTime;
                    return;

                case MouseEventType.RightClick:
                    RightClick(sender, args);
                    return;

                case MouseEventType.DoubleClick:
                    DoubleClick(sender, args);
                    return;

                case MouseEventType.Move:
                    MouseMove(sender, args);
                    return;

                case MouseEventType.DragBegin:
                    DragBegin(sender, args);
                    return;

                case MouseEventType.DragEnd:
                    DragEnd(sender, args);
                    return;

                case MouseEventType.Draging:
                    Draging(sender, args);
                    return;

                default:
                    Console.WriteLine("Unknown mouse event type.");
                    return;
            }
        }

        internal void SetFirstResponder()
        {
            Window.Resize += (sender, args) =>
                {
                    MainControl.Frame = args.To;
                };

            GlfwInputState.OnKey += (sender, args) =>
                {
                    if (s_focusedChild != null)
                        s_focusedChild.RawKeyChange(this, args);
                };

            GlfwInputState.OnCharClicked += (sender, args) =>
                {
                    if (s_focusedChild != null)
                        s_focusedChild.CharPress(sender, args);
                };

            GlfwInputState.OnMouseClick += (sender, args) =>
                {
                    if (GlfwInputState.MouseStates[0].State == TriState.None && GlfwInputState.MouseStates[1].State == TriState.None)
                        return;

                    // =====   Rebuild command chain   ======================================================
                    RebuildCommandChain(GlfwInputState.MouseLocation);
                    Control active = GetEndOfCommandChain();

                    // =====   If Left/Right - Pressed, focus the control   ======================================================
                    if (GlfwInputState.MouseStates[0].State == TriState.Pressed || GlfwInputState.MouseStates[1].State == TriState.Pressed)
                    {
                        s_focusedChild = null;

                        // Walk up the chain, set focus flags
                        Control cursor = active;
                        while (cursor.Parent != null)
                        {
                            if (cursor.CanFocus)
                            {
                                if (s_focusedChild == null)
                                    s_focusedChild = cursor;

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

                    // =====   Process Left - Pressed   ======================================================
                    if (GlfwInputState.MouseStates[0].State == TriState.Pressed)
                    {
                        active.IsClickDown = true;
                    }

                    // =====   Process Left - Up   ======================================================
                    if (GlfwInputState.MouseStates[0].State == TriState.Up)
                    {
                        // Forward event for further processing
                        active.ProcessMouseEvent(
                            this,
                            new MouseEventArgs
                            {
                                EventType = MouseEventType.Click,
                                ScreenLocation = GlfwInputState.MouseLocation
                            }
                        );

                        if (IsDraging)
                        {
                            active.ProcessMouseEvent(
                                this,
                                new MouseEventArgs
                                {
                                    EventType = MouseEventType.DragEnd,
                                    ScreenLocation = GlfwInputState.MouseLocation
                                });

                            IsDraging = false;
                        }

                        active.IsClickDown = false;
                    }

                    // =====   Process Right - Pressed   ======================================================
                    if (GlfwInputState.MouseStates[1].State == TriState.Pressed)
                    {
                        active.IsRightClickDown = true;
                    }

                    // =====   Process Right - Up   ======================================================
                    if (GlfwInputState.MouseStates[1].State == TriState.Up)
                    {
                        // Forward event for further processing
                        active.ProcessMouseEvent(
                            this,
                            new MouseEventArgs
                            {
                                EventType = MouseEventType.RightClick,
                                ScreenLocation = GlfwInputState.MouseLocation
                            }
                        );

                        active.IsRightClickDown = false;
                    }

                    // =====   Forward Raw Mouse   ======================================================
                    active.RawMouseClick(this, args);
                };

            GlfwInputState.OnMouseMove += (sender, args) =>
                {
                    // Rebuild command chain
                    RebuildCommandChain(GlfwInputState.MouseLocation);
                    Control active = GetEndOfCommandChain();

                    Input.IsSuppressingUpdate = (m_activeChild != null);

                    // Process specialized events
                    if (active.IsClickDown)
                    {
                        if (!IsDraging)
                        {
                            IsDraging = true;
                            active.ProcessMouseEvent(
                                this,
                                new MouseEventArgs
                                {
                                    EventType = MouseEventType.DragBegin,
                                    ScreenLocation = GlfwInputState.MouseLocation
                                });
                        }

                        else
                        {
                            active.ProcessMouseEvent(
                                this,
                                new MouseEventArgs
                                {
                                    EventType = MouseEventType.Draging,
                                    ScreenLocation = GlfwInputState.MouseLocation
                                }
                            );
                        }
                    }

                    else
                    {
                        active.ProcessMouseEvent(
                            this,
                            new MouseEventArgs
                            {
                                EventType = MouseEventType.Move,
                                ScreenLocation = GlfwInputState.MouseLocation
                            }
                        );
                    }

                    // =====   Forward Raw Mouse   ======================================================
                    active.RawMouseMove(this, args);
                };
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
