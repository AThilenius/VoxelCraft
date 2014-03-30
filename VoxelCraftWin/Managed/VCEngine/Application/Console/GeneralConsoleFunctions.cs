using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public static class GeneralConsoleFunctions
    {
        public static Window SelectedWindow;

        [ConsoleFunction("Clears the Console.")]
        public static String Cls(String[] args)
        {
            Console.Clear();
            return "";
        }

        [ConsoleFunction("Selects a VCWindow by title name.", "Window")]
        public static String Select(String[] args)
        {
            String fullName = args.Combine(1);

            foreach ( Window window in Window.ActiveWindows )
                if (window.Title.ToLower().StartsWith(fullName.ToLower()))
                {
                    SelectedWindow = window;
                    return "Window Selected: " + window.Title;
                }

            return "Cannot find a window that starts with the title: " + fullName;
        }

        [ConsoleFunction("Displays all active windows.", "Window")]
        public static String All(String[] args)
        {
            foreach (Window window in Window.ActiveWindows)
                Console.WriteLine("  - " + window.Title);

            return "";
        }

        [ConsoleFunction("Displays the selected window.", "Window")]
        public static String Selected(String[] args)
        {
            if (SelectedWindow == null)
                return "No Window Selected";
            else
                return SelectedWindow.Title;
        }

    }
}
