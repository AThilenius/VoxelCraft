using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public static class StackTraceExtensions
    {

        public static String[] ToStringPretty(this StackTrace trace, int collumnWidth)
        {
            List<String> strs = new List<String>();

            foreach (StackFrame frame in trace.GetFrames().Reverse())
            {
                String lineOfCode = File.ReadLines(frame.GetFileName()).Skip(frame.GetFileLineNumber() - 1).Take(1).First();

                lineOfCode = lineOfCode.TrimStart(' ','\t');

                if (lineOfCode.Length > collumnWidth - 3)
                    lineOfCode = lineOfCode.Substring(0, collumnWidth - 6) + "...";

                strs.Add(" - " + frame.GetMethod().Name + " - " + (new FileInfo(frame.GetFileName())).Name + " - " + frame.GetFileLineNumber() + " : " + frame.GetFileColumnNumber());
                strs.Add("   " + lineOfCode);
                strs.Add("");
            }

            return strs.ToArray();
        }

    }
}
