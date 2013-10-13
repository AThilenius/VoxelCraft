using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class HslColorPicker : Control
    {
        public Vector4 ColorHSL;
        public Color ColorRGB;

        private Rectangle m_spectrumFrame;
        private Rectangle m_saturationFrame;
        private Rectangle m_LuminosityFrame;

        public HslColorPicker()
        {
            ColorRGB = new Color(255, 0, 0, 255);
            ColorHSL = Color.RgbaToHsl(ColorRGB);

            Click += OnClick;
            Draging += OnClick;
        }

        void OnClick(object sender, MouseEventArgs e)
        {
            if (m_spectrumFrame.IsPointWithin(e.ScreenLocation))
            {
                float value = (e.ScreenLocation.X - m_spectrumFrame.X) / (float)m_spectrumFrame.Width;
                ColorHSL = new Vector4(value, ColorHSL.Y, ColorHSL.Z, ColorHSL.W);
                ColorRGB = Color.HslToRgba(ColorHSL);
            }

            else if (m_saturationFrame.IsPointWithin(e.ScreenLocation))
            {
                float value = (e.ScreenLocation.X - m_saturationFrame.X) / (float)m_saturationFrame.Width;
                ColorHSL = new Vector4(ColorHSL.X, value, ColorHSL.Z, ColorHSL.W);
                ColorRGB = Color.HslToRgba(ColorHSL);
            }

            else if (m_LuminosityFrame.IsPointWithin(e.ScreenLocation))
            {
                float value = (e.ScreenLocation.X - m_LuminosityFrame.X) / (float)m_LuminosityFrame.Width;
                ColorHSL = new Vector4(ColorHSL.X, ColorHSL.Y, value, ColorHSL.W);
                ColorRGB = Color.HslToRgba(ColorHSL);
            }
        }

        protected override void Draw()
        {
            // Don't draw base
            Rectangle sf = ScreenFrame;
            int delta = (int)(sf.Height / 7.0f);

            Gui.DrawBorderedRect(sf, Color.Trasparent, ColorRGB, 10);

            m_spectrumFrame = new Rectangle(sf.X + 20, sf.Y + delta * 5, sf.Width - 40, delta);
            m_saturationFrame = new Rectangle(sf.X + 20, sf.Y + delta * 3, sf.Width - 40, delta);
            m_LuminosityFrame = new Rectangle(sf.X + 20, sf.Y + delta * 1, sf.Width - 40, delta);

            DrawColorSpectrum(m_spectrumFrame, ColorHSL.Y, ColorHSL.Z);
            DrawSauration(m_saturationFrame, new Color(255, 0, 0, 255), ColorHSL.Z);
            DrawLuminosity(m_LuminosityFrame, new Color(255, 0, 0, 255), ColorHSL.Y);

            // Draw selection rectangles
            Rectangle spectrumSelect = new Rectangle(m_spectrumFrame.X + (int)(m_spectrumFrame.Width * ColorHSL.X) - 5, m_spectrumFrame.Y - 5, 10, m_spectrumFrame.Height + 10);
            Rectangle saturationSelect = new Rectangle(m_saturationFrame.X + (int)(m_saturationFrame.Width * ColorHSL.Y) - 5, m_saturationFrame.Y - 5, 10, m_saturationFrame.Height + 10);
            Rectangle luminocitySelect = new Rectangle(m_LuminosityFrame.X + (int)(m_LuminosityFrame.Width * ColorHSL.Z) - 5, m_LuminosityFrame.Y - 5, 10, m_LuminosityFrame.Height + 10);

            Gui.DrawBorderedRect(spectrumSelect, Color.Trasparent, ColorRGB, 2);
            Gui.DrawBorderedRect(saturationSelect, Color.Trasparent, ColorRGB, 2);
            Gui.DrawBorderedRect(luminocitySelect, Color.Trasparent, ColorRGB, 2);
        }

        private static void DrawDualToneQuad(Rectangle frame, Color left, Color right)
        {
            GuiRectVerticie ll = new GuiRectVerticie(new Point(frame.X, frame.Y), left);
            GuiRectVerticie ul = new GuiRectVerticie(new Point(frame.X, frame.Y + frame.Height), left);

            GuiRectVerticie lr = new GuiRectVerticie(new Point(frame.X + frame.Width, frame.Y), right);
            GuiRectVerticie ur = new GuiRectVerticie(new Point(frame.X + frame.Width, frame.Y + frame.Height), right);

            Gui.AddVerticie(ul);
            Gui.AddVerticie(ll);
            Gui.AddVerticie(lr);

            Gui.AddVerticie(ul);
            Gui.AddVerticie(lr);
            Gui.AddVerticie(ur);
        }

        private static void DrawColorSpectrum(Rectangle frame, float s, float l)
        {
            int qWidth = (int)(frame.Width / 6.0f);
            Color grey = new Color(127, 127, 127, 255);

            Color red = Color.Lerp(grey, new Color(255, 0, 0, 255), s);
            Color yellow = Color.Lerp(grey, new Color(255, 255, 0, 255), s);
            Color green = Color.Lerp(grey, new Color(0, 255, 0, 255), s);
            Color teal = Color.Lerp(grey, new Color(0, 255, 255, 255), s);
            Color blue = Color.Lerp(grey, new Color(0, 0, 255, 255), s);
            Color purple = Color.Lerp(grey, new Color(255, 0, 255, 255), s);

            if (l < 0.5f)
            {
                // Darken
                float d = 1.0f - (l / 0.5f);
                red = Color.Lerp(red, Color.Black, d);
                yellow = Color.Lerp(yellow, Color.Black, d);
                green = Color.Lerp(green, Color.Black, d);
                teal = Color.Lerp(teal, Color.Black, d);
                blue = Color.Lerp(blue, Color.Black, d);
                purple = Color.Lerp(purple, Color.Black, d);
            }
            else if (l > 0.5f)
            {
                // Lighten
                float li = (l - 0.5f) / 0.5f;
                red = Color.Lerp(red, Color.White, li);
                yellow = Color.Lerp(yellow, Color.White, li);
                green = Color.Lerp(green, Color.White, li);
                teal = Color.Lerp(teal, Color.White, li);
                blue = Color.Lerp(blue, Color.White, li);
                purple = Color.Lerp(purple, Color.White, li);
            }

            DrawDualToneQuad(new Rectangle(frame.X + qWidth * 0, frame.Y, qWidth, frame.Height), red, yellow);
            DrawDualToneQuad(new Rectangle(frame.X + qWidth * 1, frame.Y, qWidth, frame.Height), yellow, green);
            DrawDualToneQuad(new Rectangle(frame.X + qWidth * 2, frame.Y, qWidth, frame.Height), green, teal);
            DrawDualToneQuad(new Rectangle(frame.X + qWidth * 3, frame.Y, qWidth, frame.Height), teal, blue);
            DrawDualToneQuad(new Rectangle(frame.X + qWidth * 4, frame.Y, qWidth, frame.Height), blue, purple);
            DrawDualToneQuad(new Rectangle(frame.X + qWidth * 5, frame.Y, qWidth, frame.Height), purple, red);
        }

        private static void DrawSauration(Rectangle frame, Color color, float l)
        {
            Color colored = color;
            Color grey = new Color(127, 127, 127, 255);

            if (l < 0.5f)
            {
                // Darken
                float d = 1.0f - (l / 0.5f);
                colored = Color.Lerp(colored, Color.Black, d);
                grey = Color.Lerp(grey, Color.Black, d);
            }
            else if (l > 0.5f)
            {
                // Lighten
                float li = (l - 0.5f) / 0.5f;
                colored = Color.Lerp(colored, Color.White, li);
                grey = Color.Lerp(grey, Color.White, li);
            }

            DrawDualToneQuad(frame, grey, colored);
        }

        private static void DrawLuminosity(Rectangle frame, Color color, float s)
        {
            Color midColor = Color.Lerp(new Color(127, 127, 127, 255), color, s);

            DrawDualToneQuad(new Rectangle(frame.X, frame.Y, (int)(frame.Width / 2.0f), frame.Height), new Color(0, 0, 0, 255), midColor);
            DrawDualToneQuad(new Rectangle(frame.X + (int)(frame.Width / 2.0f), frame.Y, (int)(frame.Width / 2.0f), frame.Height), midColor, new Color(255, 255, 255, 255));
        }

    }
}
