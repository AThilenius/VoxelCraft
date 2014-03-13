﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.Concurrent;
using System.Runtime.InteropServices;

namespace VCEngine
{
    public class LogEntry
    {
        public enum SeverityRating : int
        {
            Info    = 0,
            Warning = 1,
            Error   = 2
        }

        public String Message;
        public String Catagory;
        public SeverityRating Severity;
    }

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void LogHandler ( int severity, String catagory, String message );

    public static class Log
    {
        public static System.ConsoleColor DefaultColor = ConsoleColor.White;
        public static System.ConsoleColor InfoColor = ConsoleColor.White;
        public static System.ConsoleColor WarningColor = ConsoleColor.Yellow;
        public static System.ConsoleColor ErrorColor = ConsoleColor.Red;


        private static bool m_printAllToConsole = false;
        private static List<LogEntry> m_logEntries = new List<LogEntry>();
        private static Dictionary<String, List<LogEntry>> m_logEntriesByCategory = new Dictionary<String, List<LogEntry>>();
        private static HashSet<String> m_activeCatagories = new HashSet<String>();

        public static void Info(String info, String catagory = "Default")
        {
            AddToLog(new LogEntry { Message = info, Catagory = catagory, Severity = LogEntry.SeverityRating.Info });
        }

        public static void Warning(String info, String catagory = "Default")
        {
            AddToLog(new LogEntry { Message = info, Catagory = catagory, Severity = LogEntry.SeverityRating.Warning });
        }

        public static void Error(String info, String catagory = "Default")
        {
            AddToLog(new LogEntry { Message = info, Catagory = catagory, Severity = LogEntry.SeverityRating.Error });
        }

        public static void LogUnManaged(int severity, String catagory, String message)
        {
            AddToLog(new LogEntry { Message = message, Catagory = catagory, Severity = (LogEntry.SeverityRating) severity });
        }

        private static void AddToLog(LogEntry entry)
        {
            m_logEntries.Add(entry);
            
            if ( !m_logEntriesByCategory.ContainsKey(entry.Catagory))
                m_logEntriesByCategory.Add(entry.Catagory, new List<LogEntry>());

            m_logEntriesByCategory[entry.Catagory].Add(entry);

            if(m_printAllToConsole && !m_activeCatagories.Contains(entry.Catagory))
                m_activeCatagories.Add(entry.Catagory);

            if (m_activeCatagories.Contains(entry.Catagory))
                PrintEntry(entry);
        }
        
        private static void PrintEntry(LogEntry entry)
        {
            switch (entry.Severity)
            {
                case LogEntry.SeverityRating.Info:
                    Console.ForegroundColor = InfoColor;
                    break;

                case LogEntry.SeverityRating.Warning:
                    Console.ForegroundColor = WarningColor;
                    break;

                case LogEntry.SeverityRating.Error:
                    Console.ForegroundColor = ErrorColor;
                    break;
            }

            Console.WriteLine("| {0,-10} | {1,-60} |", entry.Catagory, entry.Message);
        }

        #region Console Commands

        [ConsoleFunction("Prints all known log categories.", "Log")]
        public static String Categories(String[] args)
        {
            Console.ForegroundColor = InfoColor;

            foreach (String cat in m_logEntriesByCategory.Keys)
                Console.WriteLine("  - " + cat);

            Console.ForegroundColor = DefaultColor;
            return "";
        }

        [ConsoleFunction("Prints all active categories", "Log")]
        public static String Active(String[] args)
        {
            Console.ForegroundColor = InfoColor;

            foreach (String cat in m_activeCatagories)
                Console.WriteLine("  -" + cat);

            Console.ForegroundColor = DefaultColor;
            return "";
        }

        [ConsoleFunction("Prints all log entries", "Log")]
        public static String PrintAll(String[] args)
        {
            for (int i = 0; i < m_logEntries.Count; i++)
                PrintEntry(m_logEntries[i]);

            Console.ForegroundColor = DefaultColor;
            return "";
        }

        [ConsoleFunction("Prints log entries in a specified category(s).", "Log")]
        public static String PrintCategories(String[] args)
        {
            for (int categoryI = 1; categoryI < args.Length; categoryI++)
            {
                for (int i = 0; i < m_logEntries.Count; i++)
                    if (m_logEntries[i].Catagory.ToLower() == args[categoryI].ToLower())
                        PrintEntry(m_logEntries[i]);
            }

            Console.ForegroundColor = DefaultColor;
            return "";
        }

        [ConsoleFunction("Prints all non-filtered log entries.", "Log")]
        public static String PrintActive(String[] args)
        {
            for (int i = 0; i < m_logEntries.Count; i++)
                if (m_activeCatagories.Contains(m_logEntries[i].Catagory))
                    PrintEntry(m_logEntries[i]);

            Console.ForegroundColor = DefaultColor;
            return "";
        }

        [ConsoleFunction("Filters any entries NOT in categories list", "Log")]
        public static String FilterAllBut(String[] args)
        {
            m_activeCatagories.Clear();

            for (int i = 1; i < args.Length; i++)
                if (!m_activeCatagories.Contains(args[i]))
                    m_activeCatagories.Add(args[i]);

            Console.ForegroundColor = DefaultColor;
            return "";
        }

        #endregion



    }
}
