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

class VCTexture : public VCMarshalableObject
{
public:
	~VCTexture(void);

	void Bind(int texUnit);
	void SetUVWrapMode ( GLenum uMode, GLenum vMode );
	void SetFilterMode ( GLenum minFilter, GLenum magFilter );

	static VCTexture* CreateEmpty(VCTextureParams params, int width, int height);

public:
	GLuint GLTextID;
	std::string FullPath;

private:
	VCTexture(void);
	static VCTexture* CreateFromFile ( std::string path, VCTextureParams params );
	static VCTexture* ManageExistingBuffer (GLuint bufferId);

private:
	static VCTexture* m_boundTexture;
	static std::unordered_map<std::string, VCTexture*> m_loadedTextures;

	friend class VCRenderStage;
	friend class VCResourceManager;
};
