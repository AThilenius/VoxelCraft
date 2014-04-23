using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;

namespace VCEngine
{
    public abstract class FileReaper
    {
        private List<FileSystemWatcher> m_watchers = new List<FileSystemWatcher>();

        private static List<FileReaper> m_reaperInstances = new List<FileReaper>();

        public FileReaper(String[] filter)
        {
            Project.OnProjectLoaded += (projS, projA) =>
            {
                // Disable the old watchers, if any
                m_watchers.ForEach(w => w.EnableRaisingEvents = false);
                m_watchers.Clear();

                // Create a filtered files of new files not in our project
                var filesQuary = Directory.EnumerateFiles(Project.ActiveProjectDirectory, "*.*", SearchOption.AllDirectories)
                    .Where(s =>
                        {
                            for ( int i = 0; i < filter.Length; i++ )
                                if (s.EndsWith(filter[i], StringComparison.OrdinalIgnoreCase) && !Contains(s))
                                    return true;

                            return false;
                        });

                // Enumerate the quary and reap files
                filesQuary.ForEach(file => ReapNew(file, PathUtilities.RelativePath(Project.ActiveProjectDirectory, file)));

                // Save the Project to disk
                Project.ActiveProject.Save();


                // Create a file system watcher for each file type
                foreach (String fileExtension in filter)
                {
                    FileSystemWatcher watcher = new FileSystemWatcher(Project.ActiveProjectDirectory, "*." + fileExtension);
                    watcher.IncludeSubdirectories = true;
                    watcher.NotifyFilter = NotifyFilters.LastWrite;

                    // Add event handlers
                    watcher.Changed += (s, a) =>
                    {
                        LoopController.MarshalActionToMainThread(() =>
                        {
                            if (Contains(a.FullPath))
                                ReapChange(a.FullPath);

                            else
                                ReapNew(a.FullPath, PathUtilities.RelativePath(Project.ActiveProjectDirectory, a.FullPath));

                            Project.ActiveProject.Save();
                        });
                    };
                    watcher.Created += (s, a) =>
                    {
                        LoopController.MarshalActionToMainThread(() =>
                        {
                            if (Contains(a.FullPath))
                                ReapChange(a.FullPath);

                            else
                                ReapNew(a.FullPath, PathUtilities.RelativePath(Project.ActiveProjectDirectory, a.FullPath));

                            Project.ActiveProject.Save();
                        });
                    };

                    // Add it to the list
                    m_watchers.Add(watcher);

                    // Begin watching.
                    watcher.EnableRaisingEvents = true;
                }
            };
        }

        [DelayedInvoke]
        private static void CreateAllReapers()
        {
            foreach (Type t in Reflection.GetSubclassesOfType(Assembly.GetExecutingAssembly(), typeof(FileReaper)))
                m_reaperInstances.Add((FileReaper)Activator.CreateInstance(t));
        }

        protected abstract void ReapNew(String fullPath, String relativePath);
        protected abstract void ReapChange(String fullPath);
        protected abstract bool Contains(String fullPath);

    }
}