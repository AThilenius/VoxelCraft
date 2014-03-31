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
	VCGLTexture(void);
	~VCGLTexture(void);

	void Bind(int texUnit);
	void UpdateFilteringParams(VCTextureParams params);

	static VCGLTexture* LoadFromFile ( std::string path, VCTextureParams params );
	static VCGLTexture* ManageExistingBuffer (GLuint bufferId);

public:
	GLuint GLTextID;
	std::string FullPath;
	static std::unordered_map<std::string, VCGLTexture*> LoadedTextures;

private:
	int m_memoryUsage;
	static VCGLTexture* m_boundTexture;

private:
	DISALLOW_COPY_AND_ASSIGN(VCGLTexture);
	friend class VCRenderStage;
	friend class VCResourceManager;
};

DLL_EXPORT_API int VCInteropTextureCreate(unsigned int glHandle, char* fullpath);
DLL_EXPORT_API void VCInteropTextureUpdateGLHandle(int handle, unsigned int newGLHandle);
DLL_EXPORT_API void VCInteropTextureSetFilterParams(int handle, VCTextureParams params);