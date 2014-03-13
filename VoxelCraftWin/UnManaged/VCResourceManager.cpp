//
//  VCResourceManager.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCResourceManager.h"

#include "VCGLShader.h"
#include "VCGLTexture.h"
#include "VCPathUtilities.h"
#include "VCMaterial.h"
#include "VCModel.h"


VCResourceManager::VCResourceManager(void)
{
}


VCResourceManager::~VCResourceManager(void)
{
}

VCGLShader* VCResourceManager::GetShader( std::string name )
{
	return VCGLShader::GetShader(name);
}

VCGLTexture* VCResourceManager::GetTexure( std::string fullPath )
{
	return VCGLTexture::LoadFromFile(fullPath, VCTextureParams());
}

VCGLTexture* VCResourceManager::GetTexure( std::string fullPath, VCTextureParams params )
{
	return VCGLTexture::LoadFromFile(fullPath, params);
}

VCGLTexture* VCResourceManager::GetTexureInAssets( std::string partPath )
{
	return VCGLTexture::LoadFromFile(VCPathUtilities::Combine(VCPathUtilities::VCAssetsPath , partPath), VCTextureParams());
}

VCGLTexture* VCResourceManager::GetTexureInAssets( std::string partPath, VCTextureParams params)
{
	return VCGLTexture::LoadFromFile(VCPathUtilities::Combine(VCPathUtilities::VCAssetsPath , partPath), params);
}

VCGLTexture* VCResourceManager::GetTexure( GLuint existingBuffer )
{
	return VCGLTexture::ManageExistingBuffer(existingBuffer);
}

VCMaterial* VCResourceManager::GetMaterialDefault()
{
	return GetMaterial(VCPathUtilities::Combine(VCPathUtilities::VCResourcePath, VC_DEFAULT_MATERIAL_PATH));
}


VCMaterial* VCResourceManager::GetMaterial( std::string fullPath )
{
	return VCMaterial::GetMaterial(fullPath);
}

VCMaterial* VCResourceManager::GetMaterialInAssets( std::string partPath )
{
	return VCMaterial::GetMaterial(VCPathUtilities::Combine(VCPathUtilities::VCAssetsPath , partPath));
}

VCModel* VCResourceManager::GetModelDefault()
{
	return GetModel(VCPathUtilities::Combine(VCPathUtilities::VCResourcePath, VC_DEFAULT_MODEL_PATH));
}

VCModel* VCResourceManager::GetModel( std::string fullPath )
{
	return VCModel::GetModel(fullPath);
}

VCModel* VCResourceManager::GetModelInAssets( std::string partPath )
{
	return VCModel::GetModel(VCPathUtilities::Combine(VCPathUtilities::VCAssetsPath , partPath));
}

int VCInteropResourceManagerGetTexture( char* fullPath )
{
	VCGLTexture* texture = VCResourceManager::GetTexure(fullPath);
	return texture->Handle;
}
