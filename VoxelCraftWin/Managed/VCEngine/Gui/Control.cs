using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Control
    {
        public String Name;
        public Rectangle ScreenFrame;
        public Control Parent;
        public Color BackgroundColor = Color.ControlLight;
        public int BorderWidth = 1;
        public Color BorderColor = Color.ControlVeryDark;
        public Color HighlightBackgroundColor = Color.White;
        public Color HightlightBorderColor = Color.ControlBorder;
        public bool Enabled = true;
        public bool Visible = true;
        public String Font = "Lucida Sans-13-Bold";
        public HashSet<Control> Children = new HashSet<Control>();

        //public Rectangle Frame
        //{
        //    get
        //    {
        //        if (Parent == null)
        //        {
        //            return ScreenFrame;
        //        }

        //        else
        //        {
        //            return new Rectangle(
        //                ScreenFrame.X - Parent.ScreenFrame.X,
        //                ScreenFrame.Y - Parent.ScreenFrame.Y,
        //                ScreenFrame.Width,
        //                ScreenFrame.Height);
        //        }
        //    }

        //    set
        //    {
        //        if (Parent == null)
        //        {
        //            ScreenFrame = value;
        //        }

        //        else
        //        {
        //            ScreenFrame = new Rectangle(
        //                ScreenFrame.X + Parent.ScreenFrame.X,
        //                ScreenFrame.Y + Parent.ScreenFrame.Y,
        //                ScreenFrame.Width,
        //                ScreenFrame.Height);
        //        }
        //    }
        //}

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

        public Control(Rectangle screenFrame, string name, Control parent)
        {
            ScreenFrame = screenFrame;
            Name = name;
            Parent = parent;
        }

        // Called externally
        public void Render()
        {
            Draw();

            foreach (Control ctrl in Children)
                ctrl.Render();
        }

        public virtual void Draw()
        {
            if (m_wasPointInThis)
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
            if (!m_wasPointInThis && ScreenFrame.IsPointWithin(point))
            {
                MouseEnter(this, EventArgs.Empty);
                m_wasPointInThis = true;
            }

            else if (m_wasPointInThis && !ScreenFrame.IsPointWithin(point))
            {
                MouseExit(this, EventArgs.Empty);
                m_wasPointInThis = false;
            }

            // If its in a child's frame...
            foreach (Control child in Children)
            {
                if (child.ScreenFrame.IsPointWithin(point))
                {
                    if (m_activeChild != null && m_activeChild != child)
                        m_activeChild.RebuildCommandChain(point);

                    m_activeChild = child;
                    child.RebuildCommandChain(point);

                    return;
                }
            }

            // Its in our frame, not a child's
            if (m_activeChild != null)
            {
                m_activeChild.RebuildCommandChain(point);
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
