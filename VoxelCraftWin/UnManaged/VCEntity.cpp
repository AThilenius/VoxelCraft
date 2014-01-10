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


VCEntity::VCEntity(void):
	Model(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);

	Model = VCResourceManager::GetModelDefault();

	for (int i = 0; i < Model->Meshes.size(); i++)
		Materials.push_back(VCResourceManager::GetMaterialDefault());
}


VCEntity::~VCEntity(void)
{
	Model = NULL;
}

void VCEntity::Render( VCCamera* camera )
{
	// Completely unoptimized brute force drawing.
	for (int i = 0; i < Model->Meshes.size(); i++)
	{
		VCMaterial* material = Materials[i];

		material->Bind();

		// This is bad... it will result in duplicates
		VCShader::BoundShader->SetCamera(camera);
		VCShader::BoundShader->SetModelMatrix(ModelMatrix);
		
		Model->Meshes[i].Render();
	}

}

int VCInteropEntityNew()
{
	VCEntity* entity = new VCEntity();
	return entity->Handle;
}

void VCInteropEntityRelease( int handle )
{
	VCEntity* obj = (VCEntity*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

int VCInteropEntitySetModel( int handle, char* modelPath )
{
	VCEntity* obj = (VCEntity*) VCObjectStore::Instance->GetObject(handle);
	obj->Model = VCResourceManager::GetModelInAssets(modelPath);
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
