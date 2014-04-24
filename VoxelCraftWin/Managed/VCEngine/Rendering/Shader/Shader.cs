using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace VCEngine
{
    public class Shader : MarshaledObject
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropGetShaderFromFile(String fullPath);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropReloadShader(String fullPath);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropShaderGetUniformIndex(int handle, String uniformName);


        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderBind(int handle);
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetCamera(int handle, int cameraHandle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetModelMatrix(int handle, Matrix4 modelMatrix);


        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformInt(int handle, int index, int value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformFloat(int handle, int index, float value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformVec2(int handle, int index, Vector2 value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformVec3(int handle, int index, Vector3 value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformVec4(int handle, int index, Vector4 value);

        //[DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        //extern static void VCInteropShaderSetUniformMat3(int handle, int index, Matrix3 value);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropShaderSetUniformMat4(int handle, int index, Matrix4 value);

        #endregion

        public String Name;

        [JsonIgnore]
        public String FullPath;

        public List<ShaderAttribute> Attributes = new List<ShaderAttribute>();
        public List<ShaderUniform> Uniforms = new List<ShaderUniform>();
        
        public String VertexShader = "";
        public String GeometryShader = "";
        public String FragmentShader = "";

        private static Dictionary<String, Shader> m_loadedShadersByPath = new Dictionary<String, Shader>();
        private static Dictionary<String, Shader> m_loadedShadersByName = new Dictionary<String, Shader>();
        private static Dictionary<String, FileSystemWatcher> m_fileSystemWatcher = new Dictionary<String, FileSystemWatcher>();

        private Shader()
            : base()
        {
            // Used by JSON, manually get handle
        }

        public void Bind()
        {
            VCInteropShaderBind(UnManagedHandle);
        }

        public void SetCamera(Camera camera)
        {
            VCInteropShaderSetCamera(UnManagedHandle, camera.UnManagedHandle);
        }

        public void SetModelMatrix(Matrix4 modelMatrix)
        {
            VCInteropShaderSetModelMatrix(UnManagedHandle, modelMatrix);
        }

        public void ReCompileGLSL()
        {
            VCInteropReloadShader(FullPath);
        }

        public static Shader GetByPath(String fullPath)
        {
            Shader shader = null;
            if ( !m_loadedShadersByPath.TryGetValue(fullPath, out shader) )
            {
                shader = JsonConvert.DeserializeObject<Shader>(File.ReadAllText(fullPath));
                shader.UnManagedHandle = VCInteropGetShaderFromFile(fullPath);

                foreach (ShaderUniform unif in shader.Uniforms)
                    unif.UnManagedUniformIndex = VCInteropShaderGetUniformIndex(shader.UnManagedHandle, unif.Name);

                shader.FullPath = fullPath;
                m_loadedShadersByPath.Add(fullPath, shader);

                if(!m_loadedShadersByName.ContainsKey(shader.Name))
                    m_loadedShadersByName.Add(shader.Name, shader);

                return shader;
            }

            return shader;
        }

        public static Shader GetByName(String name)
        {
            Shader shader = null;
            m_loadedShadersByName.TryGetValue(name, out shader);
            return shader;
        }

        /// <summary>
        /// Pre Caches all shaders in the directory or sub directory but does
        /// not monitor them for changes.
        /// </summary>
        /// <param name="parentPath"></param>
        public static void PreCacheShaders(String parentPath)
        {
            // Load all shaders from current directory
            foreach (String fInfo in Directory.GetFiles(parentPath, "*." + PathUtilities.ShaderExtension))
                GetByPath(fInfo);

            // Recurse down directories
            foreach (string dir in Directory.GetDirectories(parentPath))
                PreCacheShaders(dir);
        }

        /// <summary>
        /// Loads all shaders in the directory or sub directory, and monitors them
        /// for changes. The shader will be recompiled when a change is made.
        /// </summary>
        /// <param name="patentPath"></param>
        public static void PreCacheAndMonitorShader(String parentPath)
        {
            PreCacheShaders(parentPath);

            //if (m_fileSystemWatcher.ContainsKey(parentPath))
            //    return;

            //FileSystemWatcher watcher = new FileSystemWatcher(parentPath, "*." + PathUtilities.ShaderExtension);
            //watcher.IncludeSubdirectories = true;
            //watcher.NotifyFilter = NotifyFilters.LastWrite;

            //// Add event handlers.
            //watcher.Changed += (s, a) => LoopController.MarshalActionToMainThread( () => VCInteropReloadShader(a.FullPath) );
            //watcher.Created += (s, a) => LoopController.MarshalActionToMainThread( () => Shader.GetByPath(a.FullPath) );

            //// Begin watching.
            //watcher.EnableRaisingEvents = true;

            //m_fileSystemWatcher.Add(parentPath, watcher);
        }

        public void SetUniform(int index, int value)
        {
            VCInteropShaderSetUniformInt(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, float value)
        {
            VCInteropShaderSetUniformFloat(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, Vector2 value)
        {
            VCInteropShaderSetUniformVec2(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, Vector3 value)
        {
            VCInteropShaderSetUniformVec3(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, Vector4 value)
        {
            VCInteropShaderSetUniformVec4(UnManagedHandle, index, value);
        }

        public void SetUniform(int index, Matrix4 value)
        {
            VCInteropShaderSetUniformMat4(UnManagedHandle, index, value);
        }

    }
}
