//
//  VCResourceManager.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCShader;
class VCTexture;
class VCMaterial;
struct VCTextureParams;

class VCResourceManager
{
public:
	VCResourceManager();
	~VCResourceManager();

	static VCShader* GetShader (std::string name);
	static VCTexture* GetTexure (std::string fullPath);
	static VCTexture* GetTexure (std::string fullPath, VCTextureParams params);
	static VCTexture* GetTexure (GLuint existingBuffer);
	static VCTexture* VCResourceManager::GetTexureInAssets( std::string partPath );
	static VCTexture* VCResourceManager::GetTexureInAssets( std::string partPath, VCTextureParams params);
	static VCMaterial* GetMaterial (std::string fullPath);
	static VCMaterial* GetMaterialInAssets (std::string partPath);
	
};
