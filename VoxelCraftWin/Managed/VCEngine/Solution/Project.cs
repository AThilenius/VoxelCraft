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
        public String Name = "UnNamed";
        public Guid GUID = Guid.NewGuid();
        public ProjectResources Resources = new ProjectResources();

        // Statics
        public static Project ActiveProject;
        public static String ActiveProjectFilePath;
        public static String ActiveProjectDirectory;
        public static event EventHandler OnProjectLoaded = delegate { };

        public static void CreateEmpty(String fullPath, String Name)
        {
            String directory = Path.GetDirectoryName(fullPath);

            if (!Directory.Exists(directory))
                Directory.CreateDirectory(directory);

            Project proj = new Project();
            proj.Name = Name;

            // Create helper folders
            CreateDirectoryTree(directory);

            // Load the project
            ActiveProjectFilePath = Path.GetFullPath(fullPath);
            ActiveProjectDirectory = Path.GetDirectoryName(ActiveProjectFilePath);
            ActiveProject = proj;

            proj.Save();


            // Notify anyone who cares that the project changed ( like the reapers )
            OnProjectLoaded(ActiveProject, EventArgs.Empty);
        }

        public static void CreateDirectoryTree(String directoryPath)
        {
            // Resources/Materials
            {
                String fullDirPath = PathUtilities.Combine(directoryPath, @"Resources\Materials");
                if (!Directory.Exists(fullDirPath))
                    Directory.CreateDirectory(fullDirPath);
            }


            // Assets/Shader
            {
                String fullDirPath = PathUtilities.Combine(directoryPath, @"Assets\Shaders");
                if (!Directory.Exists(fullDirPath))
                    Directory.CreateDirectory(fullDirPath);
            }

            // Assets/Textures
            {
                String fullDirPath = PathUtilities.Combine(directoryPath, @"Assets\Textures");
                if (!Directory.Exists(fullDirPath))
                    Directory.CreateDirectory(fullDirPath);
            }

            // Assets/Models
            {
                String fullDirPath = PathUtilities.Combine(directoryPath, @"Assets\Models");
                if (!Directory.Exists(fullDirPath))
                    Directory.CreateDirectory(fullDirPath);
            }

            // Assets/Entities
            {
                String fullDirPath = PathUtilities.Combine(directoryPath, @"Assets\Entities");
                if (!Directory.Exists(fullDirPath))
                    Directory.CreateDirectory(fullDirPath);
            }

            // Assets/Scenes
            {
                String fullDirPath = PathUtilities.Combine(directoryPath, @"Assets\Scenes");
                if (!Directory.Exists(fullDirPath))
                    Directory.CreateDirectory(fullDirPath);
            }

            // Assets/Scripts
            {
                String fullDirPath = PathUtilities.Combine(directoryPath, @"Assets\Scripts");
                if (!Directory.Exists(fullDirPath))
                    Directory.CreateDirectory(fullDirPath);
            }
        }

        internal static void LoadProject(String path)
        {
            // Test existence
            if (!PathUtilities.TestFileExistance(path))
                return;

            // Save old project
            if (ActiveProject != null)
                ActiveProject.Save();

            // Load the project
            ActiveProjectFilePath = Path.GetFullPath(path);
            ActiveProjectDirectory = Path.GetDirectoryName(ActiveProjectFilePath);
            ActiveProject = JsonConvert.DeserializeObject<Project>(File.ReadAllText(path));

            // Notify anyone who cares that the project changed ( like the reapers )
            OnProjectLoaded(ActiveProject, EventArgs.Empty);
        }

        internal void Save()
        {
            String json = JsonConvert.SerializeObject(this, Formatting.Indented);
            File.WriteAllText(ActiveProjectFilePath, json);
        }

    }
}
