//
//  VCTexture.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCTexture.h"

VCTexturePtr VCTexture::m_boundTexture = NULL;

VCTexture::VCTexture(void)
{
}

VCTexture::~VCTexture(void)
{
	glDeleteTextures(1, &m_glTextID);
}

VCTexturePtr VCTexture::CreateTexture( const char* path, GLenum uMode, GLenum vMode, GLenum minFilter, GLenum magFilter )
{
	 VCTexture* tex = new VCTexture();
	 tex->m_glTextID = SOIL_load_OGL_texture
		 (
		 path,
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_MIPMAPS
		 );

	 glBindTexture(GL_TEXTURE_2D, tex->m_glTextID);

	 // Wrap Modes / Filtering
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uMode);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vMode);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minFilter);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilter);

	 VCTexturePtr ptr (tex);
	 m_boundTexture = ptr;
	 tex->m_weakPtr = ptr;
	 return ptr;
}

VCTexturePtr VCTexture::CreateUnfilteredTexture( const char* path )
{
	return CreateTexture(path, GL_CLAMP, GL_CLAMP, GL_NEAREST, GL_NEAREST );
}

VCTexturePtr VCTexture::CreateTrilinearTexture( const char* path )
{
	return CreateTexture(path, GL_CLAMP, GL_CLAMP, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR );
}

VCTexturePtr VCTexture::CreateAnsiotropicTexture( const char* path )
{
	VC_ERROR("Anisotropic filtering not yet implemented.");
	return NULL;
}

VCTexturePtr VCTexture::ManageExistingBuffer( GLuint bufferId )
{
	VCTexture* tex = new VCTexture();
	tex->m_glTextID = bufferId;

	VCTexturePtr ptr (tex);
	tex->m_weakPtr = ptr;
	return ptr;
}

void VCTexture::Bind( int texUnit )
{
	VCTexturePtr lockedPtr = m_weakPtr.lock();

	if (m_boundTexture == lockedPtr)
		return;

	if (texUnit >= 0)
		glActiveTexture(GL_TEXTURE0 + texUnit);

	glBindTexture(GL_TEXTURE_2D, m_glTextID);

	m_boundTexture = lockedPtr;
}


void VCTexture::SetUVWrapMode( GLenum uMode, GLenum vMode )
{
	Bind(-1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vMode);
}

void VCTexture::SetFilterMode( GLenum minFilter, GLenum magFilter )
{
	Bind(-1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilter);
}
