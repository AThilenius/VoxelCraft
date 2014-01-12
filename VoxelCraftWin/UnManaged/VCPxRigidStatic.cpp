//
//  VCPxRigidStatic.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPxRigidStatic.h"

#include "VCObjectStore.h"
#include "VCPxPhysics.h"


VCPxRigidStatic::VCPxRigidStatic(void):
	PxRigidStatic(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCPxRigidStatic::~VCPxRigidStatic(void)
{
	if(PxRigidStatic != NULL)
		PxRigidStatic->release();
}

int VCInteropPhysicsRigidStaticCreate(glm::vec3 pos, glm::vec4 quat)
{
	VCPxRigidStatic* rStatic = new VCPxRigidStatic();

	physx::PxTransform transform(physx::PxVec3(pos.x, pos.y, pos.z), physx::PxQuat(quat.x, quat.y, quat.z, quat.w));
	rStatic->PxRigidStatic = VCPxPhysics::PxPhysics->createRigidStatic(transform);
	rStatic->PxRigidActor = rStatic->PxRigidStatic;

	return rStatic->Handle;
}

void VCINteropPhysicsRigidStaticRelease(int handle)
{
	VCPxRigidStatic* obj = (VCPxRigidStatic*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}
