using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public static class StringExtensions
    {

        public static String[] FixedWidthCollumn(this String text, int width)
        {
            String[] splitWords = text.Split(' ');
            List<String> wrappedLines = new List<String>();

            String currentLine = "";
            int currentWidth = 0;

            foreach (String word in splitWords)
            {
                // Needs new line?
                if (word.Length + currentWidth + 1 > width)
                {
                    wrappedLines.Add(currentLine);
                    currentLine = "";

                    // Word itself needs to be broken apart?
                    if (word.Length > width)
                    {
                        for (int i = 0; i < word.Length; i += (width - 1))
                        {
                            currentWidth = (word.Length - i) < (width - 1) ? (word.Length - i) : (width - 1);
                            wrappedLines.Add(word.Substring(i, currentWidth) + " ");
                            currentWidth++;
                        }
                    }

                    else
                    {
                        currentWidth = word.Length + 1;
                        currentLine += word + " ";
                    }
                }

                else
                {
                    // Nope, fits on this line
                    currentLine += word + " ";
                    currentWidth += word.Length + 1;
                }
            }

            // Add the last line to the list
            wrappedLines.Add(currentLine);

            return wrappedLines.ToArray();
        }

    }
}
