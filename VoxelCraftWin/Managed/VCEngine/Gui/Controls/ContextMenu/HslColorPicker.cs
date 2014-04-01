using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class HslColorPicker : ToolContextComponent
    {
        public Vector4 ColorHSL
        {
            get { return m_colorHSL; }
            set
            {
                if (m_colorHSL == value)
                    return;

                m_colorHSL = value;
                m_colorRGB = Color.HslToRgba(value);

                OnColorChange(this, EventArgs.Empty);
            }
        }
        public Color ColorRGB
        {
            get { return m_colorRGB; }
            set
            {
                if (m_colorRGB == value)
                    return;

                m_colorRGB = value;
                m_colorHSL = Color.RgbaToHsl(value);

                OnColorChange(this, EventArgs.Empty);
            }
        }
        public float RandomMultiplier = 0.1f;
        public event EventHandler OnColorChange = delegate { };

        private Vector4 m_colorHSL;
        private Color m_colorRGB;

        private Rectangle m_spectrumFrame;
        private Rectangle m_saturationFrame;
        private Rectangle m_LuminosityFrame;
        private Rectangle m_randomFrame;

        public HslColorPicker(Window window) : base (window, "HSL Color Picker")
        {
            m_colorRGB = new Color(255, 0, 0, 255);
            m_colorHSL = Color.RgbaToHsl(m_colorRGB);

            Click += OnClick;
            MouseSliding += OnClick;
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

            else if (m_randomFrame.IsPointWithin(e.ScreenLocation))
            {
                float value = (e.ScreenLocation.X - m_randomFrame.X) / (float)m_randomFrame.Width;
                //if (value > 0.95f)
                //    value = 1.0f;

                //if (value < 0.05)
                //    value = 0.0f;

                RandomMultiplier = value;
            }

            OnColorChange(this, EventArgs.Empty);
        }

        protected override void Draw()
        {
            Rectangle sf = new Rectangle(ScreenFrame.X + 5, ScreenFrame.Y + 5, ScreenFrame.Width - 10, ScreenFrame.Height - 10);
            int delta = (int)(sf.Height / 4.0f);

            //Gui.Draw9Slice(Gui.StandardTextures.Button, ScreenFrame);
            GuiDrawer.DrawBackground(ScreenFrame);
            Font.DrawStringBeveled("HSL Color", new Point(ScreenFrame.X + 10, ScreenFrame.Y + Height - 20), Color.Black);
            GuiDrawer.Draw9SliceImage(GuiDrawer.StandardTextures.Button, new Rectangle(sf.X, sf.Y, 40, sf.Height));
            GuiDrawer.DrawRectangle(new Rectangle(sf.X + 5, sf.Y + 5, 30, sf.Height - 10), ColorRGB);

            GuiDrawer.DrawRectangle(new Rectangle(sf.X + 5, sf.Y + 4, 30, 1), new Color(255, 255, 255, 128));
            GuiDrawer.DrawRectangle(new Rectangle(sf.X + 36, sf.Y + 5, 1, sf.Height - 10), new Color(255, 255, 255, 128));

            // Border
            //Gui.DrawBorderedRect(sf, Color.Trasparent, Color.Black, 2);
            //Gui.DrawBorderedRect(new Rectangle(sf.X + 2, sf.Y + 2, sf.Width - 4, sf.Height - 4), Color.Trasparent, m_colorRGB, 8);

            m_spectrumFrame = new Rectangle(sf.X + 40, sf.Y + delta * 3, sf.Width - 40, delta);
            m_saturationFrame = new Rectangle(sf.X + 40, sf.Y + delta * 2, sf.Width - 40, delta);
            m_LuminosityFrame = new Rectangle(sf.X + 40, sf.Y + delta * 1, sf.Width - 40, delta);
            m_randomFrame = new Rectangle(sf.X + 40, sf.Y + delta * 0, sf.Width - 40, delta);

            DrawColorSpectrum(m_spectrumFrame, m_colorHSL.Y, m_colorHSL.Z, m_colorRGB.A);
            DrawSauration(m_saturationFrame, m_colorRGB, m_colorHSL.Z);
            DrawLuminosity(m_LuminosityFrame, m_colorRGB, m_colorHSL.Y);
            DrawRandomSpectrum(m_randomFrame, m_colorHSL, RandomMultiplier);
            //DrawTrasparency(m_trasparentFrame, m_colorRGB);

            // Draw selection rectangles
            Rectangle spectrumSelect = new Rectangle(
                m_spectrumFrame.X + (int)(m_spectrumFrame.Width * m_colorHSL.X) - MathHelper.RoundedDevision(m_spectrumFrame.Height, 2) + 2,
                m_spectrumFrame.Y + 3, m_spectrumFrame.Height - 4, m_spectrumFrame.Height - 4);

            Rectangle saturationSelect = new Rectangle(
                m_saturationFrame.X + (int)(m_saturationFrame.Width * m_colorHSL.Y) - MathHelper.RoundedDevision(m_saturationFrame.Height, 2) + 2,
                m_saturationFrame.Y + 3, m_saturationFrame.Height - 4, m_saturationFrame.Height - 4);

            Rectangle luminocitySelect = new Rectangle(
                m_LuminosityFrame.X + (int)(m_LuminosityFrame.Width * m_colorHSL.Z) - MathHelper.RoundedDevision(m_LuminosityFrame.Height, 2) + 2,
                m_LuminosityFrame.Y + 3, m_LuminosityFrame.Height - 4, m_LuminosityFrame.Height - 4);

            Rectangle transparencySelector = new Rectangle(
                m_randomFrame.X + (int)(m_randomFrame.Width * RandomMultiplier) - MathHelper.RoundedDevision(m_randomFrame.Height, 2) + 2,
                m_randomFrame.Y + 3, m_randomFrame.Height - 4, m_randomFrame.Height - 4);

            GuiDrawer.DrawImage(GuiDrawer.StandardTextures.RoundButton, spectrumSelect);
            GuiDrawer.DrawImage(GuiDrawer.StandardTextures.RoundButton, saturationSelect);
            GuiDrawer.DrawImage(GuiDrawer.StandardTextures.RoundButton, luminocitySelect);
            GuiDrawer.DrawImage(GuiDrawer.StandardTextures.RoundButton, transparencySelector);
        }

        private void DrawDualToneQuad(Rectangle frame, Color left, Color right)
        {
            GuiRectVerticie ll = new GuiRectVerticie(new Point(frame.X, frame.Y), left);
            GuiRectVerticie ul = new GuiRectVerticie(new Point(frame.X, frame.Y + frame.Height), left);

            GuiRectVerticie lr = new GuiRectVerticie(new Point(frame.X + frame.Width, frame.Y), right);
            GuiRectVerticie ur = new GuiRectVerticie(new Point(frame.X + frame.Width, frame.Y + frame.Height), right);

            GuiDrawer.AddVerticie(ul);
            GuiDrawer.AddVerticie(ll);
            GuiDrawer.AddVerticie(lr);

            GuiDrawer.AddVerticie(ul);
            GuiDrawer.AddVerticie(lr);
            GuiDrawer.AddVerticie(ur);
        }

        private void DrawRandomSpectrum(Rectangle frame, Vector4 hsl, float spectrum)
        {
            GuiDrawer.Draw9SliceImage(GuiDrawer.StandardTextures.Button, frame);
            frame = new Rectangle(frame.X + 3, frame.Y + 4, frame.Width - 8, frame.Height - 7);

            // Draw possible spectrum
            float lower = 0.0f * spectrum - (spectrum * 0.5f);
            float upper = 1.0f * spectrum - (spectrum * 0.5f);

            Vector4 lowerHsl = hsl;
            Vector4 upperHsl = hsl;

            lowerHsl.Z += lower;
            upperHsl.Z += upper;

            lowerHsl.Z = MathHelper.Clamp(lowerHsl.Z, 0.0f, 1.0f);
            upperHsl.Z = MathHelper.Clamp(upperHsl.Z, 0.0f, 1.0f);

            Color middle = Color.HslToRgba(hsl);
            Color lowerRgb = Color.HslToRgba(lowerHsl);
            Color upperRgb = Color.HslToRgba(upperHsl);

            DrawDualToneQuad(new Rectangle(frame.X, frame.Y, frame.Width / 2, frame.Height), lowerRgb, middle);
            DrawDualToneQuad(new Rectangle(frame.X + (frame.Width / 2), frame.Y, frame.Width / 2, frame.Height), middle, upperRgb);
            GuiDrawer.DrawBorderedRect(new Rectangle(frame.X + (frame.Width / 2) - 5, frame.Y, 10, frame.Height), middle, Color.Black, 2);
            GuiDrawer.DrawRectangle(new Rectangle(frame.X, frame.Y, frame.Width, 1), Color.White);
        }

        private void DrawTrasparency(Rectangle frame, Color color)
        {
            DrawDualToneQuad(frame, new Color(color.R, color.G, color.B, 0), new Color(color.R, color.G, color.B, 255));
        }

        private void DrawColorSpectrum(Rectangle frame, float s, float l, int t)
        {
            GuiDrawer.Draw9SliceImage(GuiDrawer.StandardTextures.Button, frame);
            frame = new Rectangle(frame.X + 3, frame.Y + 4, frame.Width - 8, frame.Height - 7);

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
            GuiDrawer.DrawRectangle(new Rectangle(frame.X, frame.Y, frame.Width, 1), Color.White);
        }

        private void DrawSauration(Rectangle frame, Color color, float l)
        {
            GuiDrawer.Draw9SliceImage(GuiDrawer.StandardTextures.Button, frame);
            frame = new Rectangle(frame.X + 3, frame.Y + 4, frame.Width - 8, frame.Height - 7);

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
            GuiDrawer.DrawRectangle(new Rectangle(frame.X, frame.Y, frame.Width, 1), Color.White);
        }

        private void DrawLuminosity(Rectangle frame, Color color, float s)
        {
            GuiDrawer.Draw9SliceImage(GuiDrawer.StandardTextures.Button, frame);
            frame = new Rectangle(frame.X + 3, frame.Y + 4, frame.Width - 8, frame.Height - 7);

            Color midColor = Color.Lerp(new Color(127, 127, 127, color.A), color, s);

            DrawDualToneQuad(new Rectangle(frame.X, frame.Y, (int)(frame.Width / 2.0f), frame.Height), new Color(0, 0, 0, color.A), midColor);
            DrawDualToneQuad(new Rectangle(frame.X + (int)(frame.Width / 2.0f), frame.Y, (int)(frame.Width / 2.0f), frame.Height), midColor, new Color(255, 255, 255, color.A));
            GuiDrawer.DrawRectangle(new Rectangle(frame.X, frame.Y, frame.Width, 1), Color.White);
        }

    }
}
