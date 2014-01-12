//
//  VCPxMaterial.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCMarshalableObject.h"
#include "PxPhysicsAPI.h"

class VCPxMaterial : public VCMarshalableObject
{
public:
	VCPxMaterial();
	~VCPxMaterial();

	void Initialize(physx::PxReal staticFriction, physx::PxReal dynamicFriction, physx::PxReal restitution);

	physx::PxMaterial* PxMaterial;
};

DLL_EXPORT_API int VCInteropPhysicsPxMaterialNew();
DLL_EXPORT_API void VCInteropPhysicsPXMaterialRelease(int handle);
DLL_EXPORT_API void VCInteropPhysicsPxMaterialInitialize(int handle, float staticFriction, float dynamicFriction, float restitution);