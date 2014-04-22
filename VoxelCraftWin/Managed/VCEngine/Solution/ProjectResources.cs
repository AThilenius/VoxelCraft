using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// JSON Serializable class that acts as the parent for all resources added to the project.
    /// </summary>
    public class ProjectResources
    {
        [JsonIgnore]
        public DualKeyDictionary<Guid, String, ShaderMeta> Shaders = new DualKeyDictionary<Guid, String, ShaderMeta>();

        [JsonIgnore]
        public DualKeyDictionary<Guid, String, TextureMeta> Textures = new DualKeyDictionary<Guid, String, TextureMeta>();

        [JsonIgnore]
        public DualKeyDictionary<Guid, String, MaterialMeta> Materials = new DualKeyDictionary<Guid, String, MaterialMeta>();

        [JsonIgnore]
        public DualKeyDictionary<Guid, String, MeshMeta> Meshes = new DualKeyDictionary<Guid, String, MeshMeta>();

        [JsonIgnore]
        public DualKeyDictionary<Guid, String, ModelMeta> Models = new DualKeyDictionary<Guid, String, ModelMeta>();

        [JsonIgnore]
        public DualKeyDictionary<Guid, String, EntityMeta> Entities = new DualKeyDictionary<Guid, String, EntityMeta>();

        [JsonIgnore]
        public DualKeyDictionary<Guid, String, SceneMeta> Scenes = new DualKeyDictionary<Guid, String, SceneMeta>();


        #region Json

        [JsonPropertyAttribute("Shaders")]
        private ShaderMeta[] m_shaders;

        [JsonPropertyAttribute("Textures")]
        private TextureMeta[] m_textures;

        [JsonPropertyAttribute("Materials")]
        private MaterialMeta[] m_materials;

        [JsonPropertyAttribute("Meshes")]
        private MeshMeta[] m_meshes;

        [JsonPropertyAttribute("Models")]
        private ModelMeta[] m_models;

        [JsonPropertyAttribute("Entities")]
        private EntityMeta[] m_entities;

        [JsonPropertyAttribute("Scenes")]
        private SceneMeta[] m_scenes;

        [OnSerializing]
        private void OnSerializing(StreamingContext context)
        {
            m_shaders = Shaders.KeyOneDictionary.Values.ToArray();
            m_textures = Textures.KeyOneDictionary.Values.ToArray();
            m_materials = Materials.KeyOneDictionary.Values.ToArray();
            m_meshes = Meshes.KeyOneDictionary.Values.ToArray();
            m_models = Models.KeyOneDictionary.Values.ToArray();
            m_entities = Entities.KeyOneDictionary.Values.ToArray();
            m_scenes = Scenes.KeyOneDictionary.Values.ToArray();
        }

        [OnDeserialized]
        private void OnDeserialized(StreamingContext context)
        {
            try
            {
                Shaders = new DualKeyDictionary<Guid, String, ShaderMeta>(m_shaders, val => val.GUID, val => Path.GetFullPath(PathUtilities.Combine(Project.ActiveProjectDirectory, val.RelativePath)));
                Textures = new DualKeyDictionary<Guid, String, TextureMeta>(m_textures, val => val.GUID, val => Path.GetFullPath(PathUtilities.Combine(Project.ActiveProjectDirectory, val.RelativePath)));
                Materials = new DualKeyDictionary<Guid, String, MaterialMeta>(m_materials, val => val.GUID, val => Path.GetFullPath(PathUtilities.Combine(Project.ActiveProjectDirectory, val.RelativePath)));
                Meshes = new DualKeyDictionary<Guid, String, MeshMeta>(m_meshes, val => val.GUID, val => Path.GetFullPath(PathUtilities.Combine(Project.ActiveProjectDirectory, val.RelativePath)));
                Models = new DualKeyDictionary<Guid, String, ModelMeta>(m_models, val => val.GUID, val => Path.GetFullPath(PathUtilities.Combine(Project.ActiveProjectDirectory, val.RelativePath)));
                Entities = new DualKeyDictionary<Guid, String, EntityMeta>(m_entities, val => val.GUID, val => Path.GetFullPath(PathUtilities.Combine(Project.ActiveProjectDirectory, val.RelativePath)));
                Scenes = new DualKeyDictionary<Guid, String, SceneMeta>(m_scenes, val => val.GUID, val => Path.GetFullPath(PathUtilities.Combine(Project.ActiveProjectDirectory, val.RelativePath)));
            }
            catch (Exception ex)
            {
                Log.Error("Exception caught during DeSerialization of ProjectResources: " + ex.Message, "JSON");
            }
        }

        #endregion


    }
}
