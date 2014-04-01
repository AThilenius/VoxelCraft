using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public enum TextureFiltering : int
	{
		Default = 1,
		None = 0,
		Trilinear = 1,
		Ansiotropic = 2
	};

    [StructLayout(LayoutKind.Sequential)]
    public struct TextureParams
    {
	    int SoilFlags;
	    TextureFiltering Filtering;
	    bool ClampU;
	    bool ClampV;
    };

    public class Texture : MarshaledObject
    {

        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropResourceManagerGetTexture(String fullPath);

        #endregion

        private static Dictionary<String, Texture> m_loadedTextures = new Dictionary<String, Texture>();

        public String Fullpath;

        private Texture(String fullpath)
        {
            Fullpath = fullpath;
        }

        public static Texture GetInAssets(String path)
        {
            String combinedPath = Path.Combine(PathUtilities.AssetsPath, path);
            return Get(combinedPath);
        }

        public static Texture GetInResources(String path)
        {
            return Get(Path.Combine(PathUtilities.ResourcesPath, path));
        }

        public static Texture Get(String path)
        {
            PathUtilities.TestFileExistance(path);
            Texture tex;

            if (!m_loadedTextures.TryGetValue(path, out tex))
            {
                tex = new Texture(path);
                tex.UnManagedHandle = VCInteropResourceManagerGetTexture(path);
                m_loadedTextures.Add(path, tex);
            }

            return tex;
        }

        public static Texture CreateEmpty(int width, int height)
        {
            return null;
        }

    }
}
