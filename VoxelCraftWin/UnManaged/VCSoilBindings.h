//
//  VCSoilBindings.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/30/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

DLL_EXPORT_API unsigned int VCInteropSoilLoadOGLTexture
	(
	const char *filename,
	int force_channels,
	unsigned int reuse_texture_ID,
	unsigned int flags
	);

DLL_EXPORT_API unsigned int VCInteropSoilLoadOGLCubemap
	(
	const char *x_pos_file,
	const char *x_neg_file,
	const char *y_pos_file,
	const char *y_neg_file,
	const char *z_pos_file,
	const char *z_neg_file,
	int force_channels,
	unsigned int reuse_texture_ID,
	unsigned int flags
	);

DLL_EXPORT_API unsigned int VCInteropSoilLoadOGLSingleCubemap
	(
	const char *filename,
	const char face_order[6],
	int force_channels,
	unsigned int reuse_texture_ID,
	unsigned int flags
	);

DLL_EXPORT_API unsigned int VCInteropSoilLoadOGLHdrTexture
	(
		const char *filename,
		int fake_HDR_format,
		int rescale_to_max,
		unsigned int reuse_texture_ID,
		unsigned int flags
	);

DLL_EXPORT_API unsigned int VCInteropSoilLoadOGLTextureFromMemory
	(
		unsigned char* buffer,
		int buffer_length,
		int force_channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
	);

DLL_EXPORT_API unsigned int VCInteropSoilLoadOGLCubemapFromMemory
	(
		const unsigned char *const x_pos_buffer,
		int x_pos_buffer_length,
		const unsigned char *const x_neg_buffer,
		int x_neg_buffer_length,
		const unsigned char *const y_pos_buffer,
		int y_pos_buffer_length,
		const unsigned char *const y_neg_buffer,
		int y_neg_buffer_length,
		const unsigned char *const z_pos_buffer,
		int z_pos_buffer_length,
		const unsigned char *const z_neg_buffer,
		int z_neg_buffer_length,
		int force_channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
	);

DLL_EXPORT_API unsigned int VCInteropSoilLoadOGLSingleCubemapFromMemory
	(
		const unsigned char *const buffer,
		int buffer_length,
		const char face_order[6],
		int force_channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
	);

DLL_EXPORT_API unsigned int VCInteropSoilCreateOGLTexture
	(
		void* data,
		int width, int height, int channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
	);

DLL_EXPORT_API unsigned int VCInteropSoilCreateOGLSingleCubemap
	(
		const unsigned char *const data,
		int width, int height, int channels,
		const char face_order[6],
		unsigned int reuse_texture_ID,
		unsigned int flags
	);

DLL_EXPORT_API int VCInteropSoilSaveScreenshot
	(
		const char *filename,
		int image_type,
		int x, int y,
		int width, int height
	);

DLL_EXPORT_API void* VCInteropSoilLoadImage
	(
		const char *filename,
		int *width, int *height, int *channels,
		int force_channels
	);

DLL_EXPORT_API unsigned char* VCInteropSoilLoadImageFromMemory
	(
		const unsigned char *const buffer,
		int buffer_length,
		int *width, int *height, int *channels,
		int force_channels
	);

DLL_EXPORT_API int VCInteropSoilSaveImage
	(
		const char *filename,
		int image_type,
		int width, int height, int channels,
		const unsigned char *const data
	);

DLL_EXPORT_API void VCInteropSoilFreeImageData
	(
		void* img_data
	);

DLL_EXPORT_API const char* VCInteropSoilLastResult
	(
		void
	);