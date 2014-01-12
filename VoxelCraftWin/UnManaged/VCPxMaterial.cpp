//
//  VCPxMaterial.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPxMaterial.h"
#include "VCPxPhysics.h"
#include "VCObjectStore.h"


VCPxMaterial::VCPxMaterial(void) :
	PxMaterial(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCPxMaterial::~VCPxMaterial(void)
{
	if (PxMaterial != NULL)
	{
		PxMaterial->release();
		PxMaterial = NULL;
	}
}

void VCPxMaterial::Initialize(physx::PxReal staticFriction, physx::PxReal dynamicFriction, physx::PxReal restitution)
{
	PxMaterial = VCPxPhysics::PxPhysics->createMaterial(staticFriction, dynamicFriction, restitution);
	std::cout << "Px Material created." << std::endl;
}

int VCInteropPhysicsPxMaterialNew()
{
	VCPxMaterial* material = new VCPxMaterial();
	return material->Handle;
}

void VCInteropPhysicsPXMaterialRelease( int handle )
{
	VCPxMaterial* obj = (VCPxMaterial*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

void VCInteropPhysicsPxMaterialInitialize( int handle, float staticFriction, float dynamicFriction, float restitution )
{
	VCPxMaterial* obj = (VCPxMaterial*) VCObjectStore::Instance->GetObject(handle);
	obj->Initialize(staticFriction, dynamicFriction, restitution);
}
