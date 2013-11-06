//
//  VCTexture.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/30/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCPoolableResource.h"

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

class VCTexture : public VCPoolableResource<VCTexture, VCTextureParams>
{
public:
	~VCTexture(void);

	static VCTexturePtr ManageExistingBuffer (GLuint bufferId);

	void Bind(int texUnit);
	void SetUVWrapMode ( GLenum uMode, GLenum vMode );
	void SetFilterMode ( GLenum minFilter, GLenum magFilter );
	static VCTexture* Create ( std::string path, VCTextureParams params );

private:
	VCTexture(void);

private:
	static VCTexturePtr m_boundTexture;
	GLuint m_glTextID;

};
