//
//  VCTexture.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCMarshalableObject.h"

struct VCTextureFiltering
{
	enum Value
	{
		Default = 1,
		None = 0,
		Trilinear = 1,
		Ansiotropic = 2
	};
};

struct VCTextureParams
{
	VCTextureParams() :
		SoilFlags(SOIL_FLAG_MIPMAPS),
		Filtering(VCTextureFiltering::Default),
		ClampU(true),
		ClampV(true)
	{
	}

	int SoilFlags;
	VCTextureFiltering::Value Filtering;
	bool ClampU;
	bool ClampV;
};

class VCGLTexture : public VCMarshalableObject
{
public:
	~VCGLTexture(void);

	void Bind(int texUnit);
	void SetUVWrapMode ( GLenum uMode, GLenum vMode );
	void SetFilterMode ( GLenum minFilter, GLenum magFilter );

	static VCGLTexture* CreateEmpty(VCTextureParams params, int width, int height);
	static VCGLTexture* LoadFromFile ( std::string path, VCTextureParams params );
	static VCGLTexture* ManageExistingBuffer (GLuint bufferId);

public:
	GLuint GLTextID;
	std::string FullPath;

private:
	VCGLTexture(void);


private:
	static VCGLTexture* m_boundTexture;
	static std::unordered_map<std::string, VCGLTexture*> m_loadedTextures;

private:
	DISALLOW_COPY_AND_ASSIGN(VCGLTexture);
	friend class VCRenderStage;
	friend class VCResourceManager;
};