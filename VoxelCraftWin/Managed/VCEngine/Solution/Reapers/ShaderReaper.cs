using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// Reaps new, changed, or deleted *.vcshader files from the parent project's path
    /// and handles recompilation of the HLSL code.
    /// </summary>
    public static class ShaderReaper
    {
        private static FileSystemWatcher m_watcher;

        [DelayedInvoke]
        private static void BindReaper()
        {
            Project.OnProjectLoaded += (projS, projA) =>
                {
                    // Disable the old watcher
                    if (m_watcher != null)
                        m_watcher.EnableRaisingEvents = false;

                    // Re-Scan all files for changes
                    foreach (String path in Directory.GetFiles(Project.ActiveProjectDirectory, "*.vcshader", SearchOption.AllDirectories))
                    {
                        // skip shaders already added to the project
                        if (Project.ActiveProject.Resources.Shaders.ContainsKey(path))
                            continue;

                        // Load the GL Shader, create a ShaderMeta for it and add it to the project
                        Shader shader = Shader.GetByPath(path);
                        String relativePath = PathUtilities.RelativePath(Project.ActiveProjectDirectory, path);
                        ShaderMeta shaderMeta = new ShaderMeta { Name = shader.Name, RelativePath = relativePath, GLShader = shader };

                        Project.ActiveProject.Resources.Shaders.Add(shaderMeta.GUID, relativePath, shaderMeta);
                    }

                    Project.ActiveProject.Save();

                    // Create a new FileSystemWatcher
                    m_watcher = new FileSystemWatcher(Project.ActiveProjectDirectory, "*.vcshader");
                    m_watcher.IncludeSubdirectories = true;
                    m_watcher.NotifyFilter = NotifyFilters.LastWrite;

                    // Add event handlers
                    m_watcher.Changed += (s, a) =>
                    {
                        LoopController.MarshalActionToMainThread(() =>
                            {
                                // Load the GL Shader, create a ShaderMeta for it and add it to the project
                                Shader shader = Shader.GetByPath(a.FullPath);

                                // Already loaded into project?
                                if (Project.ActiveProject.Resources.Shaders.ContainsKey(a.FullPath))
                                {
                                    // Recompile and return
                                    shader.ReCompileGLSL();
                                    return;
                                }

                                String relativePath = PathUtilities.RelativePath(Project.ActiveProjectDirectory, a.FullPath);
                                ShaderMeta shaderMeta = new ShaderMeta { Name = shader.Name, RelativePath = relativePath, GLShader = shader };

                                Project.ActiveProject.Resources.Shaders.Add(shaderMeta.GUID, a.FullPath, shaderMeta);
                                Project.ActiveProject.Save();
                            });
                    };
                    m_watcher.Created += (s, a) =>
                    {
                        LoopController.MarshalActionToMainThread(() =>
                            {
                                // Load the GL Shader, create a ShaderMeta for it and add it to the project
                                Shader shader = Shader.GetByPath(a.FullPath);

                                // Already loaded into project (No idea how that could happen...but)?
                                if (Project.ActiveProject.Resources.Shaders.ContainsKey(a.FullPath))
                                {
                                    // Recompile and return
                                    shader.ReCompileGLSL();
                                    return;
                                }

                                String relativePath = PathUtilities.RelativePath(Project.ActiveProjectDirectory, a.FullPath);
                                ShaderMeta shaderMeta = new ShaderMeta { Name = shader.Name, RelativePath = relativePath, GLShader = shader };

                                Project.ActiveProject.Resources.Shaders.Add(shaderMeta.GUID, a.FullPath, shaderMeta);
                                Project.ActiveProject.Save();
                            });
                    };

                    // Begin watching.
                    m_watcher.EnableRaisingEvents = true;
                };
        }

    }
}
