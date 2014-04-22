using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class PathUtilities
    {
        #region Bindings

		[DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropPathSetPath(int id, String path);

        #endregion

        // Names
        public static String ProjectExtension = "ATProj";

        // Resources
        public static String WorkingDirectory { get { return Environment.CurrentDirectory; } }
        public static String ResourcesPath { get { return Path.GetFullPath(PathUtilities.Combine(Environment.CurrentDirectory, @"..\Resources")); } }
        public static String FontsPath { get { return PathUtilities.Combine(ResourcesPath, @"FontsCache"); } }
        public static String ImagesPath { get { return PathUtilities.Combine(ResourcesPath, @"Images"); } }
        public static String ShadersPath { get { return PathUtilities.Combine(ResourcesPath, @"Shaders"); } }
        public static String LoadersPath { get { return PathUtilities.Combine(ResourcesPath, @"Loaders"); } }
        public static String BMFontPath { get { return PathUtilities.Combine(LoadersPath, @"BMFont"); } }

        // Assets
        public static String AssetsPath { get { return Path.GetFullPath(PathUtilities.Combine(Environment.CurrentDirectory, @"..\Assets")); } }
        public static String MeshesPath { get { return PathUtilities.Combine(ResourcesPath, @"Meshes"); } }

        public static void UpdatePathUtilities()
        {
            VCInteropPathSetPath(0, ResourcesPath);
            VCInteropPathSetPath(1, FontsPath);
            VCInteropPathSetPath(2, ImagesPath);
            VCInteropPathSetPath(3, ShadersPath);
            VCInteropPathSetPath(4, LoadersPath);
            VCInteropPathSetPath(5, BMFontPath);
            VCInteropPathSetPath(6, AssetsPath);
            VCInteropPathSetPath(7, MeshesPath);
        }

        public static bool TestFileExistance(string fullPath)
        {
            if (!File.Exists(fullPath))
            {
                Log.Warning("Failed to find file: " + fullPath, "Resources");
                return false;
            }

            return true;
        }

        public static String Combine(String left, String right)
        {
             right = right.TrimStart('\\', '/');
             return Path.Combine(left, right);
        }

        public static String RelativePath(String projectPath, String fullPath)
        {
            return fullPath.Remove(0, projectPath.Length);
        }

        public static String RelativePath(String fullpath)
        {
            String[] splits = {"Assets", "Resources"};
            String[] subStrs = fullpath.Split(splits, StringSplitOptions.None);

            subStrs[1] = subStrs[1].Trim('\\', '/');

            return subStrs[1];
        }
    }
}
