using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class HslColorPicker : Control
    {
        public Vector4 ColorHSL
        {
            get { return m_colorHSL; }
            set
            {
                m_colorHSL = value;
                m_colorRGB = Color.HslToRgba(value);
            }
        }
        public Color ColorRGB
        {
            get { return m_colorRGB; }
            set
            {
                m_colorRGB = value;
                m_colorHSL = Color.RgbaToHsl(value);
            }
        }

        private Vector4 m_colorHSL;
        private Color m_colorRGB;

        private Rectangle m_spectrumFrame;
        private Rectangle m_saturationFrame;
        private Rectangle m_LuminosityFrame;
        private Rectangle m_trasparentFrame;

        public HslColorPicker()
        {
            m_colorRGB = new Color(255, 0, 0, 255);
            m_colorHSL = Color.RgbaToHsl(m_colorRGB);

            Click += OnClick;
            Draging += OnClick;
        }

        void OnClick(object sender, MouseEventArgs e)
        {
            if (m_spectrumFrame.IsPointWithin(e.ScreenLocation))
            {
                float value = (e.ScreenLocation.X - m_spectrumFrame.X) / (float)m_spectrumFrame.Width;
                m_colorHSL = new Vector4(value, m_colorHSL.Y, m_colorHSL.Z, m_colorHSL.W);
                m_colorRGB = Color.HslToRgba(m_colorHSL);
            }

            else if (m_saturationFrame.IsPointWithin(e.ScreenLocation))
            {
                float value = (e.ScreenLocation.X - m_saturationFrame.X) / (float)m_saturationFrame.Width;
                if (value > 0.95f)
                    value = 1.0f;

                m_colorHSL = new Vector4(m_colorHSL.X, value, m_colorHSL.Z, m_colorHSL.W);
                m_colorRGB = Color.HslToRgba(m_colorHSL);
            }

            else if (m_LuminosityFrame.IsPointWithin(e.ScreenLocation))
            {
                float value = (e.ScreenLocation.X - m_LuminosityFrame.X) / (float)m_LuminosityFrame.Width;
                if (value > 0.475f && value < 0.525)
                    value = 0.5f;

                m_colorHSL = new Vector4(m_colorHSL.X, m_colorHSL.Y, value, m_colorHSL.W);
                m_colorRGB = Color.HslToRgba(m_colorHSL);
            }

            else if (m_trasparentFrame.IsPointWithin(e.ScreenLocation))
            {
                float value = (e.ScreenLocation.X - m_trasparentFrame.X) / (float)m_trasparentFrame.Width;
                if (value > 0.95f)
                    value = 1.0f;

                if (value < 0.05)
                    value = 0.0f;

                m_colorHSL = new Vector4(m_colorHSL.X, m_colorHSL.Y, m_colorHSL.Z, value);
                m_colorRGB = Color.HslToRgba(m_colorHSL);
            }
        }

        protected override void Draw()
        {
            Rectangle sf = ScreenFrame;
            int delta = (int)(sf.Height / 9.0f);

            // Draw checkered background
            bool dark = true;
            int i = 0;
            for (int x = 0; x + 10 < sf.Width; x += 10)
            {
                dark = i % 2 == 0;
                i++;

                for (int y = 0; y + 10 < sf.Height; y += 10)
                {
                    dark = !dark;

                    if (dark)
                        Gui.DrawRectangle(new Rectangle(sf.X + x, sf.Y + y, 10, 10), new Color(0, 0, 0, 63));
                }
            }

            Gui.DrawBorderedRect(sf, Color.Trasparent, m_colorRGB, 10);


            m_spectrumFrame =   new Rectangle(sf.X + 20, sf.Y + delta * 7, sf.Width - 40, delta);
            m_saturationFrame = new Rectangle(sf.X + 20, sf.Y + delta * 5, sf.Width - 40, delta);
            m_LuminosityFrame = new Rectangle(sf.X + 20, sf.Y + delta * 3, sf.Width - 40, delta);
            m_trasparentFrame = new Rectangle(sf.X + 20, sf.Y + delta * 1, sf.Width - 40, delta);

            DrawColorSpectrum(m_spectrumFrame, m_colorHSL.Y, m_colorHSL.Z, m_colorRGB.A);
            DrawSauration(m_saturationFrame, m_colorRGB, m_colorHSL.Z);
            DrawLuminosity(m_LuminosityFrame, m_colorRGB, m_colorHSL.Y);
            DrawTrasparency(m_trasparentFrame, m_colorRGB);

            // Draw selection rectangles
            Rectangle spectrumSelect = new Rectangle(m_spectrumFrame.X + (int)(m_spectrumFrame.Width * m_colorHSL.X) - 5, m_spectrumFrame.Y - 5, 10, m_spectrumFrame.Height + 10);
            Rectangle saturationSelect = new Rectangle(m_saturationFrame.X + (int)(m_saturationFrame.Width * m_colorHSL.Y) - 5, m_saturationFrame.Y - 5, 10, m_saturationFrame.Height + 10);
            Rectangle luminocitySelect = new Rectangle(m_LuminosityFrame.X + (int)(m_LuminosityFrame.Width * m_colorHSL.Z) - 5, m_LuminosityFrame.Y - 5, 10, m_LuminosityFrame.Height + 10);
            Rectangle transparencySelector = new Rectangle(m_trasparentFrame.X + (int)(m_trasparentFrame.Width * m_colorHSL.W) - 5, m_trasparentFrame.Y - 5, 10, m_trasparentFrame.Height + 10);

            Gui.DrawBorderedRect(spectrumSelect, m_colorRGB, Color.Black, 2);
            Gui.DrawBorderedRect(saturationSelect, m_colorRGB, Color.Black, 2);
            Gui.DrawBorderedRect(luminocitySelect, m_colorRGB, Color.Black, 2);
            Gui.DrawBorderedRect(transparencySelector, m_colorRGB, Color.Black, 2);
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

        private static void DrawTrasparency(Rectangle frame, Color color)
        {
            DrawDualToneQuad(frame, new Color(color.R, color.G, color.B, 0), new Color(color.R, color.G, color.B, 255));
        }

        private static void DrawColorSpectrum(Rectangle frame, float s, float l, int t)
        {
            int qWidth = (int)(frame.Width / 6.0f);
            Color grey = new Color(127, 127, 127, t);
            Color black = new Color(0, 0, 0, t);
            Color white = new Color(255, 255, 255, t);

            Color red = Color.Lerp(grey, new Color(255, 0, 0, t), s);
            Color yellow = Color.Lerp(grey, new Color(255, 255, 0, t), s);
            Color green = Color.Lerp(grey, new Color(0, 255, 0, t), s);
            Color teal = Color.Lerp(grey, new Color(0, 255, 255, t), s);
            Color blue = Color.Lerp(grey, new Color(0, 0, 255, t), s);
            Color purple = Color.Lerp(grey, new Color(255, 0, 255, t), s);

            if (l < 0.5f)
            {
                // Darken
                float d = 1.0f - (l / 0.5f);
                red = Color.Lerp(red, black, d);
                yellow = Color.Lerp(yellow, black, d);
                green = Color.Lerp(green, black, d);
                teal = Color.Lerp(teal, black, d);
                blue = Color.Lerp(blue, black, d);
                purple = Color.Lerp(purple, black, d);
            }
            else if (l > 0.5f)
            {
                // Lighten
                float li = (l - 0.5f) / 0.5f;
                red = Color.Lerp(red, white, li);
                yellow = Color.Lerp(yellow, white, li);
                green = Color.Lerp(green, white, li);
                teal = Color.Lerp(teal, white, li);
                blue = Color.Lerp(blue, white, li);
                purple = Color.Lerp(purple, white, li);
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
            Color grey = new Color(127, 127, 127, color.A);
            Color black = new Color(0, 0, 0, color.A);
            Color white = new Color(255, 255, 255, color.A);

            if (l < 0.5f)
            {
                // Darken
                float d = 1.0f - (l / 0.5f);
                colored = Color.Lerp(colored, black, d);
                grey = Color.Lerp(grey, black, d);
            }

            else if (l > 0.5f)
            {
                // Lighten
                float li = (l - 0.5f) / 0.5f;
                colored = Color.Lerp(colored, white, li);
                grey = Color.Lerp(grey, white, li);
            }

            DrawDualToneQuad(frame, grey, colored);
        }

        private static void DrawLuminosity(Rectangle frame, Color color, float s)
        {
            Color midColor = Color.Lerp(new Color(127, 127, 127, color.A), color, s);

            DrawDualToneQuad(new Rectangle(frame.X, frame.Y, (int)(frame.Width / 2.0f), frame.Height), new Color(0, 0, 0, color.A), midColor);
            DrawDualToneQuad(new Rectangle(frame.X + (int)(frame.Width / 2.0f), frame.Y, (int)(frame.Width / 2.0f), frame.Height), midColor, new Color(255, 255, 255, color.A));
        }

    }
}
