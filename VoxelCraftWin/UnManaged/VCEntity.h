//
//  VCEntity.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/28/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCModel;
class VCMaterial;

#include "VCMarshalableObject.h"

class VCEntity : public VCMarshalableObject
{
public:
	VCEntity();
	~VCEntity();

	void Render(glm::mat4& viewProjMatrix);
	
public:
	glm::mat4 ModelMatrix;
	VCModel* Model;
	std::vector<VCMaterial*> Materials;
};

// CTor / DTor
DLL_EXPORT_API int VCInteropEntityNew();
DLL_EXPORT_API void VCInteropEntityRelease(int handle);

// Matrix
DLL_EXPORT_API void VCInteropEntitySetModelMatrix(int handle, glm::mat4 modelMatrix);

// Model / Material
DLL_EXPORT_API int VCInteropEntitySetModel(int handle, char* modelPath);
DLL_EXPORT_API void  VCInteropEntitySetMaterial(int handle, int matIndex, char* materialPath);