//
//  VCMaterial.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/24/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCGLShader;
class VCShaderValue;
class VCCamera;

class VCMaterial
{
public:
	~VCMaterial();
	void Bind();

public:
	std::string Name;
	VCGLShader* Shader;

	// Must be a pointer or the object will slice :,(
	std::vector<VCShaderValue*> Values;

private:
	VCMaterial();
	static VCMaterial* GetMaterial(std::string fullPath);

private:
	static std::unordered_map<std::string, VCMaterial*> m_loadedMaterial;
	friend class VCResourceManager;
};
