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

        // Resources
        public static String ResourcesPath { get { return Path.Combine(Environment.CurrentDirectory, @"..\Resources"); } }
        public static String FontsPath { get { return Path.Combine(ResourcesPath, @"FontsCache"); } }
        public static String ImagesPath { get { return Path.Combine(ResourcesPath, @"Images"); } }
        public static String ShadersPath { get { return Path.Combine(ResourcesPath, @"Shaders"); } }
        public static String LoadersPath { get { return Path.Combine(ResourcesPath, @"Loaders"); } }
        public static String BMFontPath { get { return Path.Combine(LoadersPath, @"BMFont"); } }

        // Assets
        public static String AssetsPath { get { return Path.Combine(Environment.CurrentDirectory, @"..\Assets"); } }
        public static String MeshesPath { get { return Path.Combine(ResourcesPath, @"Meshes"); } }

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
    }
}
