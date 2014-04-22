using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    //public class SolutionDescription
    //{
    //    public String Name;
    //    public String SolutionGUID;
    //    public String SolutionPath;

    //    public String ShadersPath;
    //    public String TexturesPath;
    //    public String MaterialsPath;
    //    public String ModelsPath;

    //    private const String DefaultAssetsPath = @"Assets";
    //    private const String DefaultShadersPath = DefaultAssetsPath + @"\Shaders";
    //    private const String DefaultTexturesPath = DefaultAssetsPath + @"\Textures";
    //    private const String DefaultMaterialsPath = DefaultAssetsPath + @"\Materials";
    //    private const String DefaultModelsPath = DefaultAssetsPath + @"\Models";

    //    // Creates a new solution at the specified path
    //    public static SolutionDescription Create (String path, String name)
    //    {
    //        SolutionDescription solution = new SolutionDescription();
    //        solution.Name = name;
    //        solution.SolutionGUID = Guid.NewGuid().ToString();
    //        solution.SolutionPath = PathUtilities.Combine(path, name);

    //        solution.ShadersPath = PathUtilities.Combine(solution.SolutionPath, DefaultShadersPath);
    //        solution.TexturesPath = PathUtilities.Combine(solution.SolutionPath, DefaultTexturesPath);
    //        solution.MaterialsPath = PathUtilities.Combine(solution.SolutionPath, DefaultMaterialsPath);
    //        solution.ModelsPath = PathUtilities.Combine(solution.SolutionPath, DefaultModelsPath);

    //        if (!Directory.Exists(solution.SolutionPath))
    //            Directory.CreateDirectory(solution.SolutionPath);

    //        if (!Directory.Exists(solution.ShadersPath))
    //            Directory.CreateDirectory(solution.ShadersPath);

    //        if (!Directory.Exists(solution.TexturesPath))
    //            Directory.CreateDirectory(solution.TexturesPath);

    //        if (!Directory.Exists(solution.MaterialsPath))
    //            Directory.CreateDirectory(solution.MaterialsPath);

    //        if (!Directory.Exists(solution.ModelsPath))
    //            Directory.CreateDirectory(solution.ModelsPath);

    //        return solution;
    //    }


    //}
}
