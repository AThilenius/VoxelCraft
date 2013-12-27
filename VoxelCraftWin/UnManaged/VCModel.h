//
//  VCModel.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/26/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "assimp/mesh.h"
#include "VCMesh.h"

class VCModel
{
public:
	~VCModel();

private:
	VCModel();
	static VCModel* GetModel(std::string& Filename);

public:
	std::vector<VCMesh> Meshes;

private:
	static std::unordered_map<std::string, VCModel*> m_loadedModels;
	friend class VCResourceManager;

};
