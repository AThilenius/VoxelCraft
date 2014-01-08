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
class VCCamera;

#include "VCMarshaledGameObject.h"

class VCEntity : public VCMarshaledGameObject
{
public:
	VCEntity();
	~VCEntity();

	void Render(VCCamera* camera);

public:
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