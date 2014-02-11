//
//  VCResourceManager.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#define VC_DEFAULT_MODEL_PATH "Defaults\\DefaultModel.obj"
#define VC_DEFAULT_MATERIAL_PATH "Defaults\\DefaultMaterial.vcmaterial"

class VCShader;
class VCTexture;
class VCMaterial;
class VCModel;
struct VCTextureParams;

class VCResourceManager
{
public:
	VCResourceManager();
	~VCResourceManager();

	// Shader
	static VCShader* GetShader (std::string name);

	// Texture
	static VCTexture* GetTexure (std::string fullPath);
	static VCTexture* GetTexure (std::string fullPath, VCTextureParams params);
	static VCTexture* GetTexure (GLuint existingBuffer);
	static VCTexture* GetTexureInAssets( std::string partPath );
	static VCTexture* GetTexureInAssets( std::string partPath, VCTextureParams params);

	// Material
	static VCMaterial* GetMaterialDefault();
	static VCMaterial* GetMaterial (std::string fullPath);
	static VCMaterial* GetMaterialInAssets (std::string partPath);

	// Model
	static VCModel* GetModelDefault();
	static VCModel* GetModel (std::string fullPath);
	static VCModel* GetModelInAssets (std::string partPath);
	
};

DLL_EXPORT_API int VCInteropResourceManagerGetTexture(char* fullPath);