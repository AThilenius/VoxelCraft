//
//  VCResourceManager.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCResourceManager.h"

#include "VCShader.h"
#include "VCTexture.h"
#include "VCPathUtilities.h"
#include "VCMaterial.h"
#include "VCModel.h"


VCResourceManager::VCResourceManager(void)
{
}


VCResourceManager::~VCResourceManager(void)
{
}

VCShader* VCResourceManager::GetShader( std::string name )
{
	return VCShader::GetShader(name);
}

VCTexture* VCResourceManager::GetTexure( std::string fullPath )
{
	return VCTexture::CreateFromFile(fullPath, VCTextureParams());
}

VCTexture* VCResourceManager::GetTexure( std::string fullPath, VCTextureParams params )
{
	return VCTexture::CreateFromFile(fullPath, params);
}

VCTexture* VCResourceManager::GetTexureInAssets( std::string partPath )
{
	return VCTexture::CreateFromFile(VCPathUtilities::Combine(VCPathUtilities::VCAssetsPath , partPath), VCTextureParams());
}

VCTexture* VCResourceManager::GetTexureInAssets( std::string partPath, VCTextureParams params)
{
	return VCTexture::CreateFromFile(VCPathUtilities::Combine(VCPathUtilities::VCAssetsPath , partPath), params);
}

VCTexture* VCResourceManager::GetTexure( GLuint existingBuffer )
{
	return VCTexture::ManageExistingBuffer(existingBuffer);
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
	VCTexture* texture = VCResourceManager::GetTexure(fullPath);
	return texture->Handle;
}
