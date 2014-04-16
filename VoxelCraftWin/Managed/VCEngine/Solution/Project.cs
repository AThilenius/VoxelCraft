using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// JSON Serializable class. This is the parent for all needed resources of a
    /// single project.
    /// </summary>
    public class Project
    {
        // Serializable
        public Guid GUID = Guid.NewGuid();
        public String Name = "UnNamed";
        public ProjectResources Resources = new ProjectResources();

        // Non Serializable
        [JsonIgnore]
        public static Project LoadedProject;

        [JsonIgnore]
        public String ProjectFilePath;

        [JsonIgnore]
        public String ProjectDirectory;

        public static event EventHandler OnProjectLoaded = delegate { };


        internal static void LoadProject(String path)
        {
            if (!PathUtilities.TestFileExistance(path))
                return;

            if (LoadedProject != null)
                LoadedProject.Save();

            LoadedProject = JsonConvert.DeserializeObject<Project>(path);
            LoadedProject.ProjectFilePath = Path.GetFullPath(path);
            LoadedProject.ProjectDirectory = Path.GetDirectoryName(LoadedProject.ProjectFilePath);

            OnProjectLoaded(LoadedProject, EventArgs.Empty);
        }

        internal void Save()
        {
            Log.Warning("Saving Projects not yet implemented", "Development");
        }

    }
}
