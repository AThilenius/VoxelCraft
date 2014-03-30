using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public abstract class MainPageBase : Control
    {
        public abstract String Name { get; }
        protected abstract Control LeftPane { get; }
        protected abstract Control RightPane { get; }
        protected abstract Control CenterPane { get; }
        protected abstract Control LowerPane { get; }

        protected PanelsTrippleButton PanelsTrippleButton;

        public MainPageBase(Window window) : base(window)
        {
            PanelsTrippleButton = new PanelsTrippleButton(ParentWindow);

            // Left Button
            PanelsTrippleButton.LeftButton.OnDepressed += (s, a) =>
            {
                if (LeftPane != null)
                {
                    LeftPane.Visible = true;
                    LeftPane.AnimateLocation(new Point(0, 0));
                }
            };
            PanelsTrippleButton.LeftButton.OnRelease += (s, a) =>
            {
                if (LeftPane != null) 
                    LeftPane.AnimateLocation(new Point(-250, 0), () => LeftPane.Visible = false);
            };

            // Right Button
            PanelsTrippleButton.RightButton.OnDepressed += (s, a) =>
            {
                if (RightPane != null)
                {
                    RightPane.Visible = true;
                    RightPane.AnimateLocation(new Point(Width - 250, 0));
                }
            };
            PanelsTrippleButton.RightButton.OnRelease += (s, a) =>
            {
                if (RightPane != null)
                    RightPane.AnimateLocation(new Point(Width, 0), () => RightPane.Visible = false);
            };

            // Center Button
            PanelsTrippleButton.CenterButton.OnDepressed += (s, a) =>
            {
                if (LowerPane != null)
                {
                    LowerPane.Visible = true;
                    LowerPane.AnimateLocation(new Point(0, 0));
                }
            };
            PanelsTrippleButton.CenterButton.OnRelease += (s, a) =>
            {
                if (LowerPane != null)
                    LowerPane.AnimateLocation(new Point(0, -250), () => LowerPane.Visible = false);
            };

            Resize += (s, a) => ResizeHandler();
        }

        protected void ResizeHandler()
        {
            Point LocLeft =    LeftPane != null   ? new Point (PanelsTrippleButton.LeftButton.IsDepressed ? 0 : -250, 0)  : new Point(-250, 0);
            Point LocRight =   RightPane != null  ? new Point (PanelsTrippleButton.RightButton.IsDepressed ? Width - 250 : Width, 0)  : new Point(Width, 0);
            Point LocLower =   LowerPane != null  ? new Point (250 + LocLeft.X, PanelsTrippleButton.CenterButton.IsDepressed ? 0 : -250)  : new Point(250 + LocLeft.X, -250);
            Point LocCenter =  new Point (250 + LocLeft.X, 250 + LocLower.Y);

            Point SizeLeft = new Point(250, Height);
            Point SizeRight = new Point(250, Height);
            Point SizeLower = new Point(Width - (250 + LocLeft.X) - (Width - LocRight.X), 250);
            Point SizeCenter = new Point(Width - (250 + LocLeft.X) - (Width - LocRight.X), Height - (250 + LocLower.Y));


            if (LeftPane != null) LeftPane.Frame = new Rectangle(LocLeft, SizeLeft);
            if (RightPane != null) RightPane.Frame = new Rectangle(LocRight, SizeRight);
            if (LowerPane != null) LowerPane.Frame = new Rectangle(LocLower, SizeLower);
            if (CenterPane != null) CenterPane.Frame = new Rectangle(LocCenter, SizeCenter);
        }

        public virtual void OnSelected()
        {
            (ParentWindow as EditorWindow).HeaderBar.PanelsButtons = PanelsTrippleButton;
        }

        protected override void Draw()
        {
            base.Draw();

            // Ensure panel coherency
            Point LocLeft =  LeftPane  != null ? LeftPane.Location : new Point(-250, 0);
            Point LocRight = RightPane != null ? RightPane.Location : new Point(Width, 0);
            Point LocLower = LowerPane != null ? new Point(250 + LocLeft.X, LowerPane.Location.Y) : new Point(250 + LocLeft.X, -250);
            Point LocCenter = new Point(250 + LocLeft.X, 250 + LocLower.Y);

            Point SizeLeft = new Point(250, Height);
            Point SizeRight = new Point(250, Height);
            Point SizeLower = new Point(Width - (250 + LocLeft.X) - (Width - LocRight.X), 250);
            Point SizeCenter = new Point(Width - (250 + LocLeft.X) - (Width - LocRight.X), Height - (250 + LocLower.Y));


            if (LeftPane != null) LeftPane.Frame = new Rectangle(LocLeft, SizeLeft);
            if (RightPane != null) RightPane.Frame = new Rectangle(LocRight, SizeRight);
            if (LowerPane != null) LowerPane.Frame = new Rectangle(LocLower, SizeLower);
            if (CenterPane != null) CenterPane.Frame = new Rectangle(LocCenter, SizeCenter);
        }

        public virtual void OnDeselected() { }
    }
}
