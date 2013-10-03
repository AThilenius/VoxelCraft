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
        public bool Enabled = true;
        public bool Visible = true;
        public String Font = "Lucida Sans-13-Bold";
        public HashSet<Control> Children = new HashSet<Control>();

        public Rectangle Frame
        {
            get
            {
                if (Parent == null)
                {
                    return ScreenFrame;
                }

                else
                {
                    return new Rectangle(
                        ScreenFrame.X - Parent.ScreenFrame.X,
                        ScreenFrame.Y - Parent.ScreenFrame.Y,
                        ScreenFrame.Width,
                        ScreenFrame.Height);
                }
            }

            set
            {
                if (Parent == null)
                {
                    ScreenFrame = value;
                }

                else
                {
                    ScreenFrame = new Rectangle(
                        ScreenFrame.X + Parent.ScreenFrame.X,
                        ScreenFrame.Y + Parent.ScreenFrame.Y,
                        ScreenFrame.Width,
                        ScreenFrame.Height);
                }
            }
        }

        public event EventHandler<MouseEventArgs> Click;
        public event EventHandler<MouseEventArgs> RightClick;
        public event EventHandler<MouseEventArgs> DoubleClick;
        public event EventHandler<MouseEventArgs> MouseEnter;
        public event EventHandler<MouseEventArgs> MouseExit;
        public event EventHandler<MouseEventArgs> MouseMove;
        public event EventHandler<MouseEventArgs> DragBegin;
        public event EventHandler<MouseEventArgs> DragEnd;
        public event EventHandler<MouseEventArgs> Draging;

        private Control m_activeChild;

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
            // Draw background
            if (BorderWidth > 0)
                Gui.DrawBorderedRect(ScreenFrame, BackgroundColor, BorderColor, BorderWidth);

            else if (BackgroundColor != Color.Trasparent)
                Gui.DrawRectangle(ScreenFrame, BackgroundColor);
        }

        public bool ProcessMouseEvent(Object sender, MouseEventArgs args)
        {
            // Check if event was within a child's frame
            foreach (Control control in Children)
            {
                if (control.ScreenFrame.IsPointWithin(args.ScreenLocation))
                {
                    if (m_activeChild == null)
                    {
                        m_activeChild = control;

                        if (control.MouseEnter != null)
                            control.MouseEnter(sender, args);
                    }

                    // See if child wants to handle event
                    if (control.ProcessMouseEvent(sender, args))
                        return true;
                }
            }

            // I'm hading the event, was a child last handling it?
            if (m_activeChild != null)
            {
                if (m_activeChild.MouseExit != null)
                    m_activeChild.MouseExit(sender, args);

                m_activeChild = null;
            }

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

        public virtual void KeyDown ()
        {

        }

        public virtual void KeyUp()
        {

        }

    }
}
