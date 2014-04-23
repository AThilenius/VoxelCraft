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
    public class TextureParams
    {
	    TextureFiltering Filtering = TextureFiltering.Trilinear;
	    bool ClampU = true;
	    bool ClampV = true;
    };

    public class Texture : MarshaledObject
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropTextureCreate(uint glHandle, String fullPath);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropTextureUpdateGLHandle(int handle, uint newGLHandle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropTextureSetFilterParams(int handle, TextureParams parameters);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropTextureBind(int handle, int texUnit);

        #endregion

        public String Fullpath;
        public UInt32 GLHandle;
        public static Texture LoadingTexture
        {
            get
            {
                if (m_loadingTexture == null)
                    m_loadingTexture = Texture.GetInResources(@"Images\Icons\Loading.bmp", Resources.LoadType.Immediate);

                return m_loadingTexture;
            }
        }

        private static Dictionary<String, Texture> m_loadedTextures = new Dictionary<String, Texture>();
        private static Texture m_loadingTexture = null;

        private Texture(String fullpath)
        {
            Fullpath = fullpath;
        }

        public void Bind(int texUnit)
        {
            VCInteropTextureBind(UnManagedHandle, texUnit);
        }

        public static Texture GetInResources(String path, Resources.LoadType loadType = Resources.LoadType.Immediate)
        {
            return Get(PathUtilities.Combine(PathUtilities.ResourcesPath, path), loadType);
        }

        public static Texture Get(String fullPath, Resources.LoadType loadType)
        {
            fullPath = Path.GetFullPath(fullPath);
            PathUtilities.TestFileExistance(fullPath);
            
            Texture tex;
            if (!m_loadedTextures.TryGetValue(fullPath, out tex))
            {
                tex = new Texture(fullPath);
                if (loadType == Resources.LoadType.Immediate)
                {
                    // Load the texture now
                    tex.GLHandle = Soil.VCInteropSoilLoadOGLTexture(fullPath, Soil.LoadFlags.SOIL_LOAD_AUTO, 0, Soil.SoilFlags.SOIL_FLAG_MIPMAPS);
                    tex.UnManagedHandle = VCInteropTextureCreate(tex.GLHandle, fullPath);
                }

                else
                {
                    // Set it to the loading texture
                    tex.UnManagedHandle = VCInteropTextureCreate(LoadingTexture.GLHandle, fullPath);

                    // Async Load the real texture
                    Resources.EnqueueFuture(loadType, () =>
                    {

                        int width = 0, heigh = 0, channels = 0;
                        IntPtr buffer = Soil.VCInteropSoilLoadImage(fullPath, out width, out heigh, out channels, Soil.LoadFlags.SOIL_LOAD_AUTO);

                        LoopController.MarshalActionToMainThread(() =>
                            {
                                // Load it into OpenGL on the main thread
                                UInt32 glHandle = Soil.VCInteropSoilCreateOGLTexture(buffer, width, heigh, channels, 0, Soil.SoilFlags.SOIL_FLAG_MIPMAPS);
                                Soil.VCInteropSoilFreeImageData(buffer);

                                VCInteropTextureUpdateGLHandle(tex.UnManagedHandle, glHandle);
                                DiagnosticsOverlay.ManagedGLMemoryAlloced += width * heigh * channels;
                            });
                    });
                }

                VCInteropTextureSetFilterParams(tex.UnManagedHandle, new TextureParams());
                m_loadedTextures.Add(fullPath, tex);
                
	            Log.Info("Managed code loaded texture: " + fullPath, "Resources");
            }

            return tex;
        }

        public static void Reload(String fullPath, Resources.LoadType loadType)
        {
            throw new NotImplementedException();
        }

        public static Texture CreateEmpty(int width, int height)
        {
            return null;
        }

    }
}
