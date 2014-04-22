using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace VCEngine
{
    public class MainEntry
    {
        public static void Main()
        {

            // Project JSON
            //Project project = new Project { Name = "Test Project" };
            //project.Resources.Textures.Add(Guid.NewGuid(), new TextureMeta { Name = "Sample Texture One", RelativePath = @"../../Build/Something.DDS" });
            //project.Resources.Textures.Add(Guid.NewGuid(), new TextureMeta { Name = "Sample Texture Two", RelativePath = @"../../Build/Something Two.BMP" });
            //project.Resources.Textures.Add(Guid.NewGuid(), new TextureMeta { Name = "Sample Texture Two", RelativePath = @"../../Build/Something Two.DDS" });

            //String json = JsonConvert.SerializeObject(project, Formatting.Indented);
            //File.WriteAllText("ProjectJsonSample.txt", json);

            //Project deSer = JsonConvert.DeserializeObject<Project>(json);


            // Recent JSON
            //RecentProjectsList recentList = new RecentProjectsList();
            //recentList.RecentProjects.Add(DateTime.Now, 
            //    new RecentProject 
            //    { 
            //        FullPath = @"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\DevelopmentProjects\Battlefield\Battlefield.VCProj", 
            //        Name = "Battlefield" 
            //    });
            //recentList.RecentProjects.Add(DateTime.Now,
            //    new RecentProject
            //    {
            //        FullPath = @"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\DevelopmentProjects\FarCry\FarCry.VCProj",
            //        Name = "Battlefield"
            //    });
            //String json = JsonConvert.SerializeObject(recentList, Formatting.Indented);
            //String recentPath = PathUtilities.Combine(PathUtilities.WorkingDirectory, "Recent.VCJson");
            //File.WriteAllText(recentPath, json);


            // Real Main
            ConsoleFunctionLoader.RegisterUnManagedHooks();
            ConsoleFunctionLoader.AddAssembly(Assembly.GetExecutingAssembly());
            ConsoleFunctionLoader.AsyncListen();
            Editor.EditorMain();
        }

    }
}