using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class ExpandButton : Control
    {
        public Boolean IsExpanded;
        public Color BackgroundColor = new Color(112, 126, 140, 255);
        public Color HoverBackgroundColor = Color.ControlBlue;
        public event EventHandler OnExpand = delegate { };
        public event EventHandler OnCollapse = delegate { };

        public ExpandButton()
        {
            Click += (s, a) => ToggleExpandContract();
        }

        public void ToggleExpandContract()
        {
            IsExpanded = !IsExpanded;

            // Already inverted
            if (!IsExpanded)
                OnCollapse(this, EventArgs.Empty);

            else
                OnExpand(this, EventArgs.Empty);
        }

        protected override void Draw()
        {
            if (IsExpanded)
            {
                if (IsHovered)
                    DrawExpandedTriangle(ScreenFrame, HoverBackgroundColor);

                else
                    DrawExpandedTriangle(ScreenFrame, BackgroundColor);
            }

            else
            {
                if (IsHovered)
                    DrawCollapsedTriangle(ScreenFrame, HoverBackgroundColor);

                else
                    DrawCollapsedTriangle(ScreenFrame, BackgroundColor);
            }

        }

        protected static void DrawCollapsedTriangle(Rectangle frame, Color color)
        {
            // Lower Left
            Gui.AddVerticie(new GuiRectVerticie(new Point(frame.X, frame.Y), color));

            // Center Right
            Gui.AddVerticie(new GuiRectVerticie(new Point(frame.X + frame.Width, frame.Y + MathHelper.RoundedDevision(frame.Height, 2)), color));

            // Upper left
            Gui.AddVerticie(new GuiRectVerticie(new Point(frame.X, frame.Y + frame.Height), color));
        }

        protected static void DrawExpandedTriangle(Rectangle frame, Color color)
        {
            // Upper left
            Gui.AddVerticie(new GuiRectVerticie(new Point(frame.X, frame.Y + frame.Height), color));

            // Lower Center
            Gui.AddVerticie(new GuiRectVerticie(new Point(frame.X + MathHelper.RoundedDevision(frame.Width, 2), frame.Y), color));

            // Upper Right
            Gui.AddVerticie(new GuiRectVerticie(new Point(frame.X + frame.Width, frame.Y + frame.Height), color));
        }
    }
}
