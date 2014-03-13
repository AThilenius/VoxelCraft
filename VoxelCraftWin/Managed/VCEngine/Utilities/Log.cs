using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.Concurrent;

namespace VCEngine
{
    public class LogEntry
    {
        public enum SeverityRating
        {
            Info,
            Warning,
            Error
        }

        public String Message;
        public String Catagory;
        public SeverityRating Severity;
    }

    public static class Log
    {

        private static List<LogEntry> m_logEntries = new List<LogEntry>();

        public static void Info(String info, String catagory = "Default")
        {
            m_logEntries.Add(new LogEntry { Message = info, Catagory = catagory, Severity = LogEntry.SeverityRating.Info });
        }

        public static void Warning(String info, String catagory = "Default")
        {
            m_logEntries.Add(new LogEntry { Message = info, Catagory = catagory, Severity = LogEntry.SeverityRating.Warning });
        }

        public static void Error(String info, String catagory = "Default")
        {
            m_logEntries.Add(new LogEntry { Message = info, Catagory = catagory, Severity = LogEntry.SeverityRating.Error });
        }

        // Console Command support
        [ConsoleFunction("Prints all log entries", "Log")]
        public static void PrintAll(String[] args)
        {
            for (int i = 0; i < m_logEntries.Count; i++)
                PrintEntry(m_logEntries[i]);

            Console.ForegroundColor = ConsoleColor.White;
        }

        
        private static void PrintEntry(LogEntry entry)
        {
            switch (entry.Severity)
            {
                case LogEntry.SeverityRating.Info:
                    Console.ForegroundColor = ConsoleColor.White;
                    break;

                case LogEntry.SeverityRating.Warning:
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    break;

                case LogEntry.SeverityRating.Error:
                    Console.ForegroundColor = ConsoleColor.Red;
                    break;
            }

            Console.WriteLine("{0,-10} - {1,-50}", entry.Catagory, entry.Message);
        }



    }
}
