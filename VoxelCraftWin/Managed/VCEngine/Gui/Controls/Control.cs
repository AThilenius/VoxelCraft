using System;
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
        //public static Control MainControl = null;
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
                m_remainingDockFrame = new Rectangle(0, 0, Frame.Width, Frame.Height);

                foreach (Control child in Children.OrderBy(ctrl => ctrl.DockOrder))
                    if (child.Visible)
                        child.Frame = child.Frame;

                args.To = m_frame;

                if (args.From != args.To)
                    Resize(this, args);
            }
        }
        public Point            Location
        {
            get { return new Point(Frame.X, Frame.Y); }
            set { Frame = new Rectangle(value, Frame.Width, Frame.Height); }
        }
        public Point            Size
        {
            get { return new Point(Frame.Width, Frame.Height); }
            set { Frame = new Rectangle(Frame.X, Frame.Y, value); }
        }
        public int              Width
        {
            get { return Frame.Width; }
            set { Frame = new Rectangle(Frame.X, Frame.Y, value, Frame.Height); }
        }
        public int              Height
        {
            get { return Frame.Height; }
            set { Frame = new Rectangle(Frame.X, Frame.Y, Frame.Width, value); }
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
        public bool             ClipView;
        public int              DockOrder;
        public Dockings         Dock = Dockings.None;
        public AutoSizeTypes    AutoSize = AutoSizeTypes.None;
        public MarginSize       Margin = new MarginSize();
        public Font             Font;


        // =====   Control   =====================================================
        public Control          Parent;
        public Window           ParentWindow;
        public int              Layer
        {
            get { return m_layer; }
            set
            {
                m_layer = value;

                if (Parent != null)
                    Parent.Children.Sort(delegate(Control l, Control r) { return l.Layer - r.Layer; });
            }
        }
        public bool             Enabled = true;
        public bool             Visible = true;
        public bool             CanFocus;
        public List<Control>    Children = new List<Control>();
        public bool             IsFocused;
        public bool             IsEventPassthrough { get; set; }
        public bool             IsHovered { get; protected set; }
        public bool             IsClickDown { get; protected set; }
        public bool             IsRightClickDown { get; protected set; }
        public bool             IsDraging { get; private set; }
        public bool             CanBeginDrag { get; set; }
        public int              DraggingThreashold = 5;


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
        public event EventHandler<MouseEventArgs>           MouseSliding = delegate { };
        public event EventHandler<CharEventArgs>            CharPress = delegate { };
        public event EventHandler<ControlFocusArgs>         Focused = delegate { };
        public event EventHandler<ResizeEventArgs>          Resize = delegate { };
        public event EventHandler<ParentChangeEventArgs>    ParentChanged = delegate { };
        public event EventHandler<DragBeginArgs>            DragBegin = delegate { };
        public event EventHandler<DragDropArgs>             DragEnter = delegate { };
        public event EventHandler<DragDropArgs>             DragExit = delegate { };
        public event EventHandler<DragDropArgs>             DragDrop = delegate { };
        public event EventHandler<DragDropArgs>             DragDraw = delegate { };


        protected Rectangle m_frame = new Rectangle();
        protected Input m_input { get { return ParentWindow.Input; } }
        protected Boolean m_isFirstResponder;
        protected GlfwInputState m_glfwInputState { get { return ParentWindow.GlfwInputState; } }
        protected GuiDrawer Gui { get { return ParentWindow.Gui; } }
        private Rectangle m_remainingDockFrame = new Rectangle();
        private Control m_activeChild;
        private int m_layer;
        private bool m_wasPointInThis;
        private double m_lastClickTime;
        private ValueAnimator<Rectangle> m_animator;

        private static Boolean m_mouseDownSomewhere;
        private static Boolean m_draggingActionInProgress;
        private static Point m_clickDownPoint = new Point();
        private static Control m_beganDraggingControl = null;
        private static Object m_draggingMessage = null;

        // =====   Debug Only   ======================================================
#if DEBUG
        private static Dictionary<Control, System.Diagnostics.StackTrace> m_allControls = new Dictionary<Control, System.Diagnostics.StackTrace>();
        private static Boolean m_renderOrphans;
        private bool m_orphanWarningIssued;
#endif

        public Control(Window window)
        {
            ParentWindow = window;
            Font = Font.GetFont("Calibri", 16, window);
            MouseEnter += (s, a) => { IsHovered = true; IsClickDown = false; };
            MouseExit += (s, a) => { IsHovered = false;  IsClickDown = false; };

#if DEBUG
            m_allControls.Add(this, new System.Diagnostics.StackTrace(true));
#endif
        }

        // Called externally
        public void Render()
        {
            // Recursively render all controls
            _Render();

            // Then allow any dragging control to render
            if (m_beganDraggingControl != null )
                m_beganDraggingControl.DragDraw(this, new DragDropArgs(m_beganDraggingControl, m_draggingMessage, m_clickDownPoint,
                            new MouseEventArgs { EventType = MouseEventType.Draging, ScreenLocation = ParentWindow.GlfwInputState.MouseLocation }));

            // Ensure we don't have any orphans
#if DEBUG
            foreach ( var KVP in m_allControls )
            {
                if (KVP.Key.Parent == null && !KVP.Key.m_isFirstResponder)
                {
                    if (!KVP.Key.m_orphanWarningIssued)
                    {
                        Log.Warning("Orphaned control of type " + KVP.Key.GetType().Name + " found.", "Gui");
                        KVP.Key.m_orphanWarningIssued = true;
                    }

                    if (m_renderOrphans)
                        Gui.DrawBorderedRect(new Rectangle(KVP.Key.ScreenFrame.X - 10, KVP.Key.ScreenFrame.Y - 10, KVP.Key.Width + 20, KVP.Key.Height + 20), Color.ControlRed, Color.Black, 1);
                }
            }
#endif
        }

        // Recursive
        private void _Render()
        {
            Draw();

            foreach (Control ctrl in Children)
                if (ctrl.Visible)
                    ctrl._Render();
        }

        public void PropagateUpdate()
        {
            Update();

            // Update animations (If animating)
            if (m_animator != null)
            {
                if (m_animator.IsDoneAnimating)
                {
                    m_animator = null;
                    return;
                }

                Frame = m_animator.GetValue();
            }

            foreach (Control ctrl in Children.ToArray())
                ctrl.PropagateUpdate();
        }

        public virtual void AddControl(Control control)
        {
            Children.Add(control);
            Children.Sort(delegate(Control l, Control r) { return l.Layer - r.Layer; });

            if (control.Parent != null)
                control.Parent.RemoveControl(control);

            // Force an update
            //Frame = Frame;
            
            ParentChangeEventArgs args = new ParentChangeEventArgs { OldParent = control.Parent, NewParent = this };
            control.Parent = this;
            control.ParentChanged(this, args);
        }

        public virtual void RemoveControl(Control control)
        {
            Children.Remove(control);
            Children.Sort(delegate(Control l, Control r) { return l.Layer - r.Layer; });

            ParentChangeEventArgs args = new ParentChangeEventArgs { OldParent = control.Parent, NewParent = null };
            control.Parent = null;
            control.ParentChanged(this, args);
        }

        public virtual void RemoveAllControls()
        {
            foreach (Control ctrl in Children)
            {
                ParentChangeEventArgs args = new ParentChangeEventArgs { OldParent = ctrl.Parent, NewParent = null };
                ctrl.Parent = null;
                ctrl.ParentChanged(this, args);
            }

            Children.Clear();
        }

        public void Focus()
        {
            s_focusedChild = null;

            // Walk up the chain, set focus flags
            Control cursor = this;
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

        public void AnimateFrame(Rectangle to, Action onCompleation = null, float animationTime = 0.25f)
        {
            m_animator = new ValueAnimator<Rectangle>(m_frame, to, animationTime);
            ParentWindow.ShouldRedraw(animationTime + 0.1f);

            if (onCompleation != null)
                m_animator.OnCompleation += (s, a) => onCompleation();
        }

        public void AnimateLocation(Point to, Action onCompleation = null, float animationTime = 0.25f)
        {
            m_animator = new ValueAnimator<Rectangle>(m_frame, new Rectangle(to, Size), animationTime);
            ParentWindow.ShouldRedraw(animationTime + 0.1f);

            if (onCompleation != null)
                m_animator.OnCompleation += (s, a) => onCompleation();
        }

        public void AnimateSize(Point to, Action onCompleation = null, float animationTime = 0.25f)
        {
            m_animator = new ValueAnimator<Rectangle>(m_frame, new Rectangle(Location, to), animationTime);
            ParentWindow.ShouldRedraw(animationTime + 0.1f);

            if (onCompleation != null)
                m_animator.OnCompleation += (s, a) => onCompleation();
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
        }

        protected virtual void Update()
        {
        }

        private void UpdateFrame(Rectangle newFrame)
        {
        }
        
        internal void SetFirstResponder()
        {
            m_isFirstResponder = true;

            ParentWindow.Resize += (sender, args) =>
                {
                    Frame = new Rectangle(0, 0, ParentWindow.ScaledSize);
                };

            ParentWindow.GlfwInputState.OnKey += (sender, args) =>
                {
                    if (s_focusedChild != null)
                        s_focusedChild.RawKeyChange(this, args);
                };

            ParentWindow.GlfwInputState.OnCharClicked += (sender, args) =>
                {
                    if (s_focusedChild != null)
                        s_focusedChild.CharPress(sender, args);
                };

            ParentWindow.GlfwInputState.OnMouseClick += (sender, args) =>
                {
                    // Wasn't left or right button
                    if (ParentWindow.GlfwInputState.MouseStates[0].State == TriState.None && ParentWindow.GlfwInputState.MouseStates[1].State == TriState.None)
                        return;

                    // =====   Rebuild command chain   ======================================================
                    RebuildCommandChain(ParentWindow.GlfwInputState.MouseLocation, false);
                    Control active = GetEndOfCommandChain();

                    // =====   If Left/Right - Pressed, focus the control   ======================================================
                    if (ParentWindow.GlfwInputState.MouseStates[0].State == TriState.Pressed || ParentWindow.GlfwInputState.MouseStates[1].State == TriState.Pressed)
                        active.Focus();

                    // =====   Process Left - Pressed   ======================================================
                    if (ParentWindow.GlfwInputState.MouseStates[0].State == TriState.Pressed)
                    {
                        active.IsClickDown = true;
                        m_clickDownPoint = args.Location;
                        m_mouseDownSomewhere = true;
                    }

                    // =====   Process Left - Up   ======================================================
                    if (ParentWindow.GlfwInputState.MouseStates[0].State == TriState.Up)
                    {

                        // If we were dragging
                        if (m_draggingActionInProgress)
                        {
                            active.DragDrop(this, new DragDropArgs(m_beganDraggingControl, m_draggingMessage, m_clickDownPoint, 
                                new MouseEventArgs { EventType = MouseEventType.Draging, ScreenLocation = ParentWindow.GlfwInputState.MouseLocation }));
                            m_draggingActionInProgress = false;
                            m_beganDraggingControl = null;
                            m_draggingMessage = null;
                        }

                        else
                        {
                            active.Click(this, new MouseEventArgs { EventType = MouseEventType.Click, ScreenLocation = ParentWindow.GlfwInputState.MouseLocation });

                            // 250ms double click
                            if (Time.CurrentTime < active.m_lastClickTime + 0.250f)
                                active.DoubleClick(sender, new MouseEventArgs { EventType = MouseEventType.DoubleClick, ScreenLocation = ParentWindow.GlfwInputState.MouseLocation });

                            active.m_lastClickTime = Time.CurrentTime;
                        }

                        active.IsClickDown = false;
                        m_mouseDownSomewhere = false;
                    }

                    // =====   Process Right - Pressed   ======================================================
                    if (ParentWindow.GlfwInputState.MouseStates[1].State == TriState.Pressed)
                    {
                        active.IsRightClickDown = true;
                    }

                    // =====   Process Right - Up   ======================================================
                    if (ParentWindow.GlfwInputState.MouseStates[1].State == TriState.Up)
                    {
                        active.RightClick(this, new MouseEventArgs { EventType = MouseEventType.RightClick, ScreenLocation = ParentWindow.GlfwInputState.MouseLocation });
                        active.IsRightClickDown = false;
                    }

                    // =====   Forward Raw Mouse   ======================================================
                    active.RawMouseClick(this, args);
                };

            ParentWindow.GlfwInputState.OnMouseMove += (sender, args) =>
            {

                // If the mouse isn't down anywhere, just handle normal enter/exit events.
                if (!m_mouseDownSomewhere)
                {
                    RebuildCommandChain(ParentWindow.GlfwInputState.MouseLocation, false);
                    Control active = GetEndOfCommandChain();
                    active.MouseMove(this, new MouseEventArgs { EventType = MouseEventType.Move, ScreenLocation = ParentWindow.GlfwInputState.MouseLocation });
                }


                Control previosActive = GetEndOfCommandChain();

                // If the mouse is down but we are NOT dragging 
                if (m_mouseDownSomewhere && !m_draggingActionInProgress)
                {
                    // then ignore all other controls ( Don't RebuildCommandChain )

                    // If the mouse is down and we SHOULD be dragging 
                    if (Point.Distance(m_clickDownPoint, ParentWindow.GlfwInputState.MouseLocation) > previosActive.DraggingThreashold && previosActive.CanBeginDrag)
                    {
                        // then DraggingBegin() fall through to next
                        m_draggingActionInProgress = true;
                        m_beganDraggingControl = previosActive;

                        // Get Drag-Begin info
                        DragBeginArgs beginArgs = new DragBeginArgs();
                        m_beganDraggingControl.DragBegin(this, beginArgs);

                        if (beginArgs.Message == null)
                            throw new Exception("A control marked to handle drag failed to respond to the DragBegin event");

                        m_draggingMessage = beginArgs.Message;
                    }

                    else
                        previosActive.MouseSliding(this, new MouseEventArgs { EventType = MouseEventType.Move, ScreenLocation = ParentWindow.GlfwInputState.MouseLocation });
                }

                // If the mouse is down and we ARE dragging
                if (m_mouseDownSomewhere && m_draggingActionInProgress)
                {
                    RebuildCommandChain(ParentWindow.GlfwInputState.MouseLocation, true);
                    Control active = GetEndOfCommandChain();

                    if (previosActive != active)
                    {
                        // then DraggingExit() / DraggingEnter() respectively
                        previosActive.DragExit(this, new DragDropArgs(m_beganDraggingControl, m_draggingMessage, m_clickDownPoint,
                            new MouseEventArgs { EventType = MouseEventType.Draging, ScreenLocation = ParentWindow.GlfwInputState.MouseLocation }));

                        active.DragEnter(this, new DragDropArgs(m_beganDraggingControl, m_draggingMessage, m_clickDownPoint,
                            new MouseEventArgs { EventType = MouseEventType.Draging, ScreenLocation = ParentWindow.GlfwInputState.MouseLocation }));
                    }

                }

                ParentWindow.Input.IsSuppressingUpdate = (m_activeChild != null);

                //active.RawMouseMove(this, args);
            };
        }

        private void RebuildCommandChain(Point point, bool suppressEvents)
        {
            if (Visible && !m_wasPointInThis && ScreenFrame.IsPointWithin(point))
            {
                if ( !suppressEvents )
                    MouseEnter(this, EventArgs.Empty);

                m_wasPointInThis = true;
            }

            // If its in a child's frame... (Iterate in reverse order)
            for(int i = Children.Count - 1; i >= 0; i--)
            {
                Control child = Children[i];

                if (child.Visible && !child.IsEventPassthrough && child.ScreenFrame.IsPointWithin(point))
                {
                    if (m_activeChild != null && m_activeChild != child)
                    {
                        Control ctrl = m_activeChild;
                        while (ctrl != null)
                        {
                            if (!suppressEvents)
                                ctrl.MouseExit(this, EventArgs.Empty);

                            ctrl.m_wasPointInThis = false;
                            ctrl = ctrl.m_activeChild;
                        }
                    }

                    m_activeChild = child;
                    child.RebuildCommandChain(point, suppressEvents);

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
                    if (!suppressEvents)
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

        #region Console Commands

#if DEBUG
        [ConsoleFunction("Boolean value for forced orphan drawing.", "Gui")]
        public static String DrawOrphans(String[] args)
        {
            m_renderOrphans = Boolean.Parse(args[1]);
            return "";
        }

        [ConsoleFunction("Prints a stack trace of all orphan controls.", "Gui")]
        public static String TraceOrphans(String[] args)
        {
            foreach (var KVP in m_allControls)
            {
                if (KVP.Key.Parent == null && !KVP.Key.m_isFirstResponder)
                {
                    Console.WriteLine("=============================================================================");
                    Console.WriteLine("= Stack Trace for Control of Type: [ " + KVP.Key.GetType().Name + " ]");
                    Console.WriteLine("=============================================================================");

                    foreach (string line in KVP.Value.ToStringPretty(60))
                        Console.WriteLine("    " + line);
                }
            }

            return "";
        }
#endif

        #endregion

    }
}
