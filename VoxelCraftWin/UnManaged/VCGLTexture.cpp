//
//  VCTexture.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCGLTexture.h"
#include "VCObjectStore.h"

VCGLTexture* VCGLTexture::m_boundTexture = NULL;
std::unordered_map<std::string, VCGLTexture*> VCGLTexture::LoadedTextures;

VCGLTexture::VCGLTexture(void):
	m_memoryUsage(0)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}

VCGLTexture::~VCGLTexture(void)
{
	glDeleteTextures(1, &GLTextID);
	g_gpuMemoryUsage -= m_memoryUsage;
}

VCGLTexture* VCGLTexture::ManageExistingBuffer( GLuint bufferId )
{
	VCGLTexture* tex = new VCGLTexture();
	tex->GLTextID = bufferId;
	return tex;
}

void VCGLTexture::Bind( int texUnit )
{
	//if (m_boundTexture == this)
	//	return;

	if (texUnit >= 0)
		glActiveTexture(GL_TEXTURE0 + texUnit);

	glBindTexture(GL_TEXTURE_2D, GLTextID);

	//m_boundTexture = this;
}

void VCGLTexture::UpdateFilteringParams( VCTextureParams params )
{
	Bind(-1);

	// Wrap Modes / Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.ClampU ? GL_CLAMP : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.ClampV ? GL_CLAMP : GL_REPEAT);

	switch (params.Filtering)
	{
	case VCTextureFiltering::None:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;

	case VCTextureFiltering::Trilinear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;

	case VCTextureFiltering::Ansiotropic:
		VC_ERROR("Anisotropic filtering not yet supported.");
		break;

	default:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	}

}

VCGLTexture* VCGLTexture::LoadFromFile( std::string path, VCTextureParams params )
{
	auto iter = LoadedTextures.find(path);

	if (iter != LoadedTextures.end())
		return iter->second;

	VCGLTexture* tex = new VCGLTexture();
	tex->FullPath = path;
	tex->GLTextID = SOIL_load_OGL_texture
		(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		params.SoilFlags
		);

	glBindTexture(GL_TEXTURE_2D, tex->GLTextID);

	// Wrap Modes / Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.ClampU ? GL_CLAMP : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.ClampV ? GL_CLAMP : GL_REPEAT);

	switch (params.Filtering)
	{
	case VCTextureFiltering::None:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;

	case VCTextureFiltering::Trilinear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;

	case VCTextureFiltering::Ansiotropic:
		VC_ERROR("Anisotropic filtering not yet supported.");
		break;

	default:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	}

	// Track Memory Usage
	int width, heigh, depth = 0;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &heigh);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_DEPTH, &depth);
	tex->m_memoryUsage = width * heigh * depth;
	g_gpuMemoryUsage += tex->m_memoryUsage;

	LoadedTextures.insert(std::unordered_map<std::string, VCGLTexture*>::value_type(path, tex));
	VCLog::Info("Un-Managed code loaded texture: " + path, "Resources");

	return tex;
}

int VCInteropTextureCreate( unsigned int glHandle, char* fullpath )
{
	VCGLTexture* tex = new VCGLTexture();
	tex->GLTextID = glHandle;
	tex->FullPath = std::string(fullpath);
	VCGLTexture::LoadedTextures.insert(std::unordered_map<std::string, VCGLTexture*>::value_type(fullpath, tex));
	return tex->Handle;
}

void VCInteropTextureUpdateGLHandle( int handle, unsigned int newGLHandle )
{
	VCGLTexture* obj = (VCGLTexture*) VCObjectStore::Instance->GetObject(handle);
	obj->GLTextID = newGLHandle;
}

void VCInteropTextureSetFilterParams( int handle, VCTextureParams params )
{
	VCGLTexture* obj = (VCGLTexture*) VCObjectStore::Instance->GetObject(handle);
	obj->UpdateFilteringParams(params);
}

void VCInteropTextureBind( int handle, int texUnit )
{
	VCGLTexture* obj = (VCGLTexture*) VCObjectStore::Instance->GetObject(handle);
	obj->Bind(texUnit);
}