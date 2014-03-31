using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public static class Soil
    {

        [Flags]
        public enum LoadFlags : int
        {
	        SOIL_LOAD_AUTO = 0,
	        SOIL_LOAD_L = 1,
	        SOIL_LOAD_LA = 2,
	        SOIL_LOAD_RGB = 3,
	        SOIL_LOAD_RGBA = 4
        };

        [Flags]
        public enum SoilFlags : int
        {
	        SOIL_FLAG_POWER_OF_TWO = 1,
	        SOIL_FLAG_MIPMAPS = 2,
	        SOIL_FLAG_TEXTURE_REPEATS = 4,
	        SOIL_FLAG_MULTIPLY_ALPHA = 8,
	        SOIL_FLAG_INVERT_Y = 16,
	        SOIL_FLAG_COMPRESS_TO_DXT = 32,
	        SOIL_FLAG_DDS_LOAD_DIRECT = 64,
	        SOIL_FLAG_NTSC_SAFE_RGB = 128,
	        SOIL_FLAG_CoCg_Y = 256,
	        SOIL_FLAG_TEXTURE_RECTANGLE = 512
        };

        [Flags]
        public enum SaveFlags : int
        {
	        SOIL_SAVE_TYPE_TGA = 0,
	        SOIL_SAVE_TYPE_BMP = 1,
	        SOIL_SAVE_TYPE_DDS = 2
        };

        public const String DdsCubeMapFaceOrder = "EWUDNS";

        [Flags]
        public enum HdrFlags : int
        {
	        SOIL_HDR_RGBE = 0,
	        SOIL_HDR_RGBdivA = 1,
	        SOIL_HDR_RGBdivA2 = 2
        };
        
        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static UInt32 VCInteropSoilLoadOGLTexture
	    (
	        String filename,
            LoadFlags force_channels,
	        UInt32 reuse_texture_ID,
            SoilFlags flags
	    );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static UInt32 VCInteropSoilLoadOGLCubemap
        (
            String x_pos_file,
            String x_neg_file,
            String y_pos_file,
            String y_neg_file,
            String z_pos_file,
            String z_neg_file,
            LoadFlags force_channels,
            UInt32 reuse_texture_ID,
            SoilFlags flags
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static UInt32 VCInteropSoilLoadOGLSingleCubemap
        (
            String filename,
            SByte face_order, // [6]
            LoadFlags force_channels,
            UInt32 reuse_texture_ID,
            SoilFlags flags
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static UInt32 VCInteropSoilLoadOGLHdrTexture
        (
            String filename,
            HdrFlags fake_HDR_format,
            int rescale_to_max,
            UInt32 reuse_texture_ID,
            SoilFlags flags
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static UInt32 VCInteropSoilLoadOGLTextureFromMemory
        (
            ref Byte[] buffer,
            int buffer_length,
            LoadFlags force_channels,
            UInt32 reuse_texture_ID,
            SoilFlags flags
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static UInt32 VCInteropSoilLoadOGLCubemapFromMemory
        (
            Byte[] x_pos_buffer,
            int x_pos_buffer_length,
            Byte[] x_neg_buffer,
            int x_neg_buffer_length,
            Byte[] y_pos_buffer,
            int y_pos_buffer_length,
            Byte[] y_neg_buffer,
            int y_neg_buffer_length,
            Byte[] z_pos_buffer,
            int z_pos_buffer_length,
            Byte[] z_neg_buffer,
            int z_neg_buffer_length,
            LoadFlags force_channels,
            UInt32 reuse_texture_ID,
            SoilFlags flags
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static UInt32 VCInteropSoilLoadOGLSingleCubemapFromMemory
        (
            Byte[] buffer,
            int buffer_length,
            Byte face_order, // [6]
            LoadFlags force_channels,
            UInt32 reuse_texture_ID,
            SoilFlags flags
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static UInt32 VCInteropSoilCreateOGLTexture
        (
            IntPtr data,
            int width, int height, int channels,
            UInt32 reuse_texture_ID,
            SoilFlags flags
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static UInt32 VCInteropSoilCreateOGLSingleCubemap
        (
            Byte[] data,
            int width, int height, int channels,
            Byte face_order, // [6]
            UInt32 reuse_texture_ID,
            SoilFlags flags
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int VCInteropSoilSaveScreenshot
        (
            String filename,
            SaveFlags image_type,
            int x, int y,
            int width, int height
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static IntPtr VCInteropSoilLoadImage
        (
            String filename,
            out int width, out int height, out int channels,
            LoadFlags force_channels
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static Byte[] VCInteropSoilLoadImageFromMemory
        (
            Byte[] buffer,
            int buffer_length,
            out int width, out int height, out int channels,
            LoadFlags force_channels
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int VCInteropSoilSaveImage
        (
            String filename,
            SaveFlags image_type,
            int width, int height, int channels,
            Byte[] data
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void VCInteropSoilFreeImageData
        (
            IntPtr img_data
        );

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static String VCInteropSoilLastResult();

    }
}
