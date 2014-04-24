using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class MaterialReaper : FileReaper
    {

        public MaterialReaper()
            : base(new string[] {PathUtilities.MaterialExtension})
        {
        }

        protected override void ReapNew(String fullPath, String relativePath)
        {
            MaterialMeta matMeta = new MaterialMeta { RelativePath = relativePath, Material = Material.Get(fullPath) };
            Project.ActiveProject.Resources.Materials.Add(matMeta.GUID, fullPath, matMeta);
        }

        protected override void ReapChange(String fullPath)
        {
            Material.ForceReload(fullPath);
        }

        protected override bool Contains(String fullPath)
        {
            return Project.ActiveProject.Resources.Materials.ContainsKey(fullPath);
        }

    }
}
