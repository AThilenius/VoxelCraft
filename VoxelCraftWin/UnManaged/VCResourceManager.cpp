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

VCMaterial* VCResourceManager::GetMaterial( std::string fullPath )
{
	return VCMaterial::GetMaterial(fullPath);
}

VCMaterial* VCResourceManager::GetMaterialInAssets( std::string partPath )
{
	return VCMaterial::GetMaterial(VCPathUtilities::Combine(VCPathUtilities::VCAssetsPath , partPath));
}
