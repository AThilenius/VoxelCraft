using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct TextMetrics
    {
        public int TotalWidth;
        public int TotalHeight;

        public TextMetrics(int width, int height)
        {
            TotalWidth = width;
            TotalHeight = height;
        }
    }

    public class Font
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiDrawText(int font, string text, Point point, Color color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropGuiGetTextMetrics(int font, string text, out TextMetrics metrics);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static string VCInteropLoadFont(string fntPath, string ddsPath, out int fontId);

        #endregion

        #region Base Config
        private const String m_baseConfig =
@"
# AngelCode Bitmap Font Generator configuration file
fileVersion=1

# font settings
fontFile=
charSet=0
aa=2
scaleH=100
useSmoothing=1
useUnicode=1
disableBoxChars=1
outputInvalidCharGlyph=0
dontIncludeKerningPairs=0
useHinting=1
renderFromOutline=0
useClearType=1

# character alignment
paddingDown=0
paddingUp=0
paddingRight=0
paddingLeft=0
spacingHoriz=1
spacingVert=1
useFixedHeight=0
forceZero=0

# output file
outWidth=256
outHeight=256
outBitDepth=32
fontDescFormat=2
fourChnlPacked=0
textureFormat=dds
textureCompression=0
alphaChnl=1
redChnl=1
greenChnl=1
blueChnl=1
invA=0
invR=0
invG=0
invB=0

# outline
outlineThickness=0

# selected chars
chars=32-126,160-255

# imported icon images
";
        #endregion

        #region Static

        public static Font DefaultFont
        {
            get
            {
                if (m_default == null)
                    m_default = Font.GetFont("Calibri", 16);
                
                return m_default;
            }
        }

        private static Dictionary<String, Font> m_loadedFonts = new Dictionary<string, Font>();
        private static Font m_default;

        public static Font GetFont (String fontName, int size, Boolean bold = false, Boolean italic = false)
        {
            size = (int)Math.Round(size * Gui.Scale);

            String description = fontName + size + (bold ? "B" : "") + (italic ? "I" : "");
            String fntPath = Path.Combine(PathUtilities.FontsPath, description + ".fnt");
            String ddsPath = Path.Combine(PathUtilities.FontsPath, description + "_0.dds");

            if (m_loadedFonts.ContainsKey(description))
                return m_loadedFonts[description];

            // Load the font
            GenerateDDS(fontName, size, bold, italic);

            int fontID;
            VCInteropLoadFont(fntPath, ddsPath, out fontID);

            Font font = new Font(fontID, fontName, size, bold, italic);
            m_loadedFonts.Add(description, font);
            return font;
        }

        private static void GenerateDDS(String font, int size, Boolean bold, Boolean italic)
        {
            String description = font + size + (bold ? "B" : "") + (italic ? "I" : "");
            String fntPath = Path.Combine(PathUtilities.FontsPath, description + ".fnt");
            String ddsPath = Path.Combine(PathUtilities.FontsPath, description + "_0.dds");
            String configPath = Path.Combine(PathUtilities.FontsPath, description + ".bmfc");

            if (File.Exists(fntPath))
                return;

            //==========   Generate Descriptor   =================================================
            if (!File.Exists(configPath))
            {
                // Create a file to write to. 
                using (StreamWriter sw = File.CreateText(configPath))
                {
                    sw.WriteLine(m_baseConfig);
                    sw.WriteLine("fontName=" + font);
                    sw.WriteLine("fontSize=" + size.ToString());
                    sw.WriteLine("isBold=" + (bold ? "1" : "0"));
                    sw.WriteLine("isItalic=" + (italic ? "1" : "0"));
                }
            }


            //==========   Invoke BMFont   =================================================
            if (!File.Exists(fntPath) || !File.Exists(ddsPath))
            {
                Console.WriteLine("========================================================================");
                Console.WriteLine("Begin: Invoking BMFont command from shell.");

                Process p = new Process();
                p.StartInfo.UseShellExecute = false;
                p.StartInfo.RedirectStandardOutput = true;
                p.StartInfo.FileName = PathUtilities.BMFontPath + @"\bmfont.exe";
                p.StartInfo.Arguments = "-c \"" + configPath + "\" -o \"" + fntPath + "\"";
                p.Start();
                string output = p.StandardOutput.ReadToEnd();
                p.WaitForExit();

                Console.WriteLine(output);
                Console.WriteLine("========================================================================");
            }
        }

        #endregion

        #region Member

        public String Name { get; private set; }
        public int Size { get; private set; }
        public Boolean Bold { get; private set; }
        public Boolean Italic { get; private set; }

        private int m_fontId;

        private Font(int Id, String font, int size, Boolean bold, Boolean italic)
        {
            m_fontId = Id;
            Name = font;
            Size = size;
            Bold = bold;
            Italic = italic;
        }

        public void DrawString(string text, Point llPoint, Color color)
        {
            llPoint = llPoint * Gui.Scale;
            VCInteropGuiDrawText(m_fontId, text, new Point(llPoint.X, llPoint.Y), color);
        }

        public TextMetrics GetMetrics(string text)
        {
            TextMetrics tm;
            VCInteropGuiGetTextMetrics(m_fontId, text, out tm);
            return tm;
        }

        #endregion

    }
}
