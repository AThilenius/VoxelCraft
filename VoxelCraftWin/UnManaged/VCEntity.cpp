//
//  VCEntity.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/28/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCEntity.h"

#include "VCObjectStore.h"
#include "VCModel.h"
#include "VCMesh.h"
#include "VCMaterial.h"
#include "VCShader.h"
#include "VCResourceManager.h"


VCEntity::VCEntity(void)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCEntity::~VCEntity(void)
{
}

void VCEntity::Render( glm::mat4& viewProjMatrix )
{

	// Completely unoptimized brute force drawing.
	for (int i = 0; i < Model->Meshes.size(); i++)
	{
		VCMaterial* material = Materials[i];

		material->Bind();
		VCShader::BoundShader->SetMVP(viewProjMatrix * ModelMatrix);
		Model->Meshes[i].Render();
	}

}

int VCInteropEntityNew()
{
	VCEntity* entity = new VCEntity();
	entity->Model = VCResourceManager::GetModelDefault();

	for (int i = 0; i < entity->Model->Meshes.size(); i++)
		entity->Materials.push_back(VCResourceManager::GetMaterialDefault());

	return entity->Handle;
}

void VCInteropEntityRelease( int handle )
{
	VCEntity* obj = (VCEntity*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

void VCInteropEntitySetModelMatrix( int handle, glm::mat4 modelMatrix )
{
	VCEntity* obj = (VCEntity*) VCObjectStore::Instance->GetObject(handle);
	obj->ModelMatrix = modelMatrix;
}

int VCInteropEntitySetModel( int handle, char* modelPath )
{
	VCEntity* obj = (VCEntity*) VCObjectStore::Instance->GetObject(handle);
	obj->Model = VCResourceManager::GetModel(modelPath);
	obj->Materials.clear();

	for (int i = 0; i < obj->Model->Meshes.size(); i++)
		obj->Materials.push_back(VCResourceManager::GetMaterialDefault());

	// Return needed Material count
	return obj->Model->Meshes.size();
}

void VCInteropEntitySetMaterial( int handle, int matIndex, char* materialPath )
{
	VCEntity* obj = (VCEntity*) VCObjectStore::Instance->GetObject(handle);
	obj->Materials[matIndex] = VCResourceManager::GetMaterial(materialPath);
}
