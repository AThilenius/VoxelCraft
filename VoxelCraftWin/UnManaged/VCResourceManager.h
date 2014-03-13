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

class VCGLShader;
class VCGLTexture;
class VCMaterial;
class VCModel;
struct VCTextureParams;

class VCResourceManager
{
public:
	VCResourceManager();
	~VCResourceManager();

	// Shader
	static VCGLShader* GetShader (std::string name);

	// Texture
	static VCGLTexture* GetTexure (std::string fullPath);
	static VCGLTexture* GetTexure (std::string fullPath, VCTextureParams params);
	static VCGLTexture* GetTexure (GLuint existingBuffer);
	static VCGLTexture* GetTexureInAssets( std::string partPath );
	static VCGLTexture* GetTexureInAssets( std::string partPath, VCTextureParams params);

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