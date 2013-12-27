//
//  VCStaticMeshRenderer.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/26/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include "VCGameObject.h"

class VCModel;
class VCMaterial;

class VCStaticMeshRenderer : public VCGameObject
{
public:
	VCStaticMeshRenderer();
	~VCStaticMeshRenderer();

	void Render();

public:
	VCModel* Model;
	std::vector<VCMaterial*> Materials;
	
};