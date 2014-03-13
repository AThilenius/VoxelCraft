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
std::unordered_map<std::string, VCGLTexture*> VCGLTexture::m_loadedTextures;

VCGLTexture::VCGLTexture(void)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}

VCGLTexture::~VCGLTexture(void)
{
	glDeleteTextures(1, &GLTextID);
}

VCGLTexture* VCGLTexture::ManageExistingBuffer( GLuint bufferId )
{
	VCGLTexture* tex = new VCGLTexture();
	tex->GLTextID = bufferId;
	return tex;
}

void VCGLTexture::Bind( int texUnit )
{
	if (m_boundTexture == this)
		return;

	if (texUnit >= 0)
		glActiveTexture(GL_TEXTURE0 + texUnit);

	glBindTexture(GL_TEXTURE_2D, GLTextID);

	m_boundTexture = this;
}


void VCGLTexture::SetUVWrapMode( GLenum uMode, GLenum vMode )
{
	Bind(-1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vMode);
}

void VCGLTexture::SetFilterMode( GLenum minFilter, GLenum magFilter )
{
	Bind(-1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilter);
}

VCGLTexture* VCGLTexture::CreateEmpty( VCTextureParams params, int width, int height )
{
	VCGLTexture* tex = new VCGLTexture();

	glGenTextures(1, &tex->GLTextID);
	glBindTexture(GL_TEXTURE_2D, tex->GLTextID);

	if (((width - 1) & width) || ((height - 1) & height))
	{
		VC_ERROR("Image must be a power of two in both Width and Height.");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);


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

	glBindTexture(GL_TEXTURE_2D, 0);
	m_boundTexture = NULL;

	return tex;
}

VCGLTexture* VCGLTexture::LoadFromFile( std::string path, VCTextureParams params )
{
	auto iter = m_loadedTextures.find(path);

	if (iter != m_loadedTextures.end())
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

	glBindTexture(GL_TEXTURE_2D, 0);
	m_boundTexture = NULL;
	m_loadedTextures.insert(std::unordered_map<std::string, VCGLTexture*>::value_type(path, tex));

	return tex;
}