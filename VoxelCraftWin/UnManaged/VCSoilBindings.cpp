//
//  VCSoilBindings.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 3/30/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCSoilBindings.h"
#include "SOIL.h"

unsigned int VCInteropSoilLoadOGLTexture
	(
	const char *filename,
	int force_channels,
	unsigned int reuse_texture_ID,
	unsigned int flags
	)
{
	return SOIL_load_OGL_texture(filename, force_channels, reuse_texture_ID, flags);
}

unsigned int VCInteropSoilLoadOGLCubemap
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
	)
{
	return SOIL_load_OGL_cubemap(x_pos_file, x_neg_file, y_pos_file, y_neg_file, z_pos_file, z_neg_file, force_channels, reuse_texture_ID, flags);
}

unsigned int VCInteropSoilLoadOGLSingleCubemap
	(
	const char *filename,
	const char face_order[6],
	int force_channels,
	unsigned int reuse_texture_ID,
	unsigned int flags
	)
{
	return SOIL_load_OGL_single_cubemap(filename, face_order, force_channels, reuse_texture_ID, flags);
}

unsigned int VCInteropSoilLoadOGLHdrTexture
	(
	const char *filename,
	int fake_HDR_format,
	int rescale_to_max,
	unsigned int reuse_texture_ID,
	unsigned int flags
	)
{
	return SOIL_load_OGL_HDR_texture(filename, fake_HDR_format, rescale_to_max, reuse_texture_ID, flags);
}

unsigned int VCInteropSoilLoadOGLTextureFromMemory
	(
	unsigned char* buffer,
	int buffer_length,
	int force_channels,
	unsigned int reuse_texture_ID,
	unsigned int flags
	)
{
	unsigned int glHandle = SOIL_load_OGL_texture_from_memory(buffer, buffer_length, force_channels, reuse_texture_ID, flags);
	return glHandle;
}

unsigned int VCInteropSoilLoadOGLCubemapFromMemory
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
	)
{
	return SOIL_load_OGL_cubemap_from_memory(
		x_pos_buffer, x_pos_buffer_length, x_neg_buffer, x_neg_buffer_length, 
		y_pos_buffer, y_pos_buffer_length, y_neg_buffer, y_neg_buffer_length, 
		z_pos_buffer, z_pos_buffer_length, z_neg_buffer, z_neg_buffer_length, 
		force_channels, reuse_texture_ID, flags);
}

unsigned int VCInteropSoilLoadOGLSingleCubemapFromMemory
	(
	const unsigned char *const buffer,
	int buffer_length,
	const char face_order[6],
	int force_channels,
	unsigned int reuse_texture_ID,
	unsigned int flags
	)
{
	return SOIL_load_OGL_single_cubemap(face_order, face_order, force_channels, reuse_texture_ID, flags);
}

unsigned int VCInteropSoilCreateOGLTexture
	(
	void* data,
	int width, int height, int channels,
	unsigned int reuse_texture_ID,
	unsigned int flags
	)
{
	return SOIL_create_OGL_texture((unsigned char*)data, width, height, channels, reuse_texture_ID, flags);
}

unsigned int VCInteropSoilCreateOGLSingleCubemap
	(
	const unsigned char *const data,
	int width, int height, int channels,
	const char face_order[6],
	unsigned int reuse_texture_ID,
	unsigned int flags
	)
{
	return SOIL_create_OGL_single_cubemap(data, width, height, channels, face_order, reuse_texture_ID, flags);
}

int VCInteropSoilSaveScreenshot
	(
	const char *filename,
	int image_type,
	int x, int y,
	int width, int height
	)
{
	return SOIL_save_screenshot(filename, image_type, x, y, width, height);
}

void* VCInteropSoilLoadImage
	(
	const char *filename,
	int *width, int *height, int *channels,
	int force_channels
	)
{
	unsigned char* charBuffer = SOIL_load_image(filename, width, height, channels, force_channels);
	return (void*) charBuffer;
}

unsigned char* VCInteropSoilLoadImageFromMemory
	(
	const unsigned char *const buffer,
	int buffer_length,
	int *width, int *height, int *channels,
	int force_channels
	)
{
	return SOIL_load_image_from_memory(buffer, buffer_length, width, height, channels, force_channels);
}

int VCInteropSoilSaveImage
	(
	const char *filename,
	int image_type,
	int width, int height, int channels,
	const unsigned char *const data
	)
{
	return SOIL_save_image(filename, image_type, width, height, channels, data);
}

void VCInteropSoilFreeImageData ( void* img_data )
{
	return SOIL_free_image_data((unsigned char*) img_data);
}

const char* VCInteropSoilLastResult ( void )
{
	return SOIL_last_result();
}