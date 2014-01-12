//
//  VCPxRigidDynamic.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPxRigidDynamic.h"

#include "VCObjectStore.h"
#include "VCPxPhysics.h"


VCPxRigidDynamic::VCPxRigidDynamic(void):
	PxRigidDynamic(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCPxRigidDynamic::~VCPxRigidDynamic(void)
{
	if(PxRigidDynamic != NULL)
		PxRigidDynamic->release();
}

int VCInteropPhysicsRigidDynamicCreate(glm::vec3 pos, glm::vec4 quat)
{
	VCPxRigidDynamic* rStatic = new VCPxRigidDynamic();

	physx::PxTransform transform(physx::PxVec3(pos.x, pos.y, pos.z), physx::PxQuat(quat.x, quat.y, quat.z, quat.w));
	rStatic->PxRigidDynamic = VCPxPhysics::PxPhysics->createRigidDynamic(transform);
	rStatic->PxRigidActor = rStatic->PxRigidDynamic;

	return rStatic->Handle;
}

void VCINteropPhysicsRigidDynamicRelease(int handle)
{
	VCPxRigidDynamic* obj = (VCPxRigidDynamic*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}
