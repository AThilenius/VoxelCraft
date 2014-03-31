﻿using System;
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

        public static Texture GetInResources(String path, Resources.LoadType loadType = Resources.LoadType.Immediate)
        {
            return Get(Path.Combine(PathUtilities.ResourcesPath, path), loadType);
        }

        public static Texture Get(String path, Resources.LoadType loadType)
        {
            path = Path.GetFullPath(path);
            PathUtilities.TestFileExistance(path);
            
            Texture tex;
            if (!m_loadedTextures.TryGetValue(path, out tex))
            {
                tex = new Texture(path);
                if (loadType == Resources.LoadType.Immediate)
                {
                    // Load the texture now
                    tex.GLHandle = Soil.VCInteropSoilLoadOGLTexture(path, Soil.LoadFlags.SOIL_LOAD_AUTO, 0, Soil.SoilFlags.SOIL_FLAG_MIPMAPS);
                    tex.UnManagedHandle = VCInteropTextureCreate(tex.GLHandle, path);
                }

                else
                {
                    // Set it to the loading texture
                    tex.UnManagedHandle = VCInteropTextureCreate(LoadingTexture.GLHandle, path);

                    // Async Load the real texture
                    Resources.EnqueueFuture(loadType, () =>
                    {

                        int width = 0, heigh = 0, channels = 0;
                        IntPtr buffer = Soil.VCInteropSoilLoadImage(path, out width, out heigh, out channels, Soil.LoadFlags.SOIL_LOAD_AUTO);

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
                m_loadedTextures.Add(path, tex);
                
	            Log.Info("Managed code loaded texture: " + path, "Resources");
            }

            return tex;
        }

        public static Texture CreateEmpty(int width, int height)
        {
            return null;
        }

    }
}
