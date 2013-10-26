using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class Slider : Control
    {
        public float Value = 1.0f;

        public Slider()
        {
            Click += OnClick;
            Draging += OnClick;
            Frame = new Rectangle(0, 0, 100, 25);
            BorderWidth = 1;
        }

        void OnClick(object sender, MouseEventArgs e)
        {
            Rectangle sf = ScreenFrame;
            Value = (e.ScreenLocation.X - sf.X) / (float)sf.Width;

            if (Value > 0.95f)
                Value = 1.0f;

            if (Value < 0.05)
                Value = 0.0f;
        }

        protected override void Draw()
        {
            // Suppress Base Drawing
            // base.Draw();

            Rectangle sf = ScreenFrame;

            // Draw Frame
            Gui.DrawBorderedRect(new Rectangle(sf.X, sf.Y + (int)(sf.Height * 0.5f) - 5, sf.Width, 10), BackgroundColor, BorderColor, BorderWidth);

            // Draw selection rectangle
            Rectangle select = new Rectangle(sf.X + (int)(sf.Width * Value) - 5, sf.Y - 5, 10, sf.Height + 10);
            Gui.DrawBorderedRect(select, HoverBackgroundColor, Color.Black, 2);

            //Gui.DrawString(Label + ": " + Value.ToString("n2"), new Point(sf.X + 10, sf.Y + 3), Color.Black);
        }

    }
}
