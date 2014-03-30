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

        public static String Combine(this String[] stringArray, int beginAt = -1, int endAt = -1)
        {
            String retString = "";
            beginAt = beginAt == -1 ? 0 : beginAt;
            endAt = endAt == -1 ? stringArray.Length - 1 : endAt;

            for (int i = beginAt; i < endAt; i++)
                if (i != endAt - 1)
                    retString += stringArray[i] + " ";
                else
                    retString += stringArray[i];

            return retString;
        }

    }
}
