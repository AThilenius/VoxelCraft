//
//  VCPxRigedActor.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPxRigidActor.h"

#include "PxPhysicsAPI.h"
#include "VCObjectStore.h"
#include "VCPxMaterial.h"
#include "VCPxShape.h"


VCPxRigidActor::VCPxRigidActor(void) :
	PxRigidActor(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCPxRigidActor::~VCPxRigidActor(void)
{
}

void VCInteropPhysicsRigidActorAttachShape( int handle, int shapeHandle )
{
	VCPxRigidActor* obj = (VCPxRigidActor*) VCObjectStore::Instance->GetObject(handle);
	VCPxShape* shape = (VCPxShape*) VCObjectStore::Instance->GetObject(shapeHandle);

	obj->PxRigidActor->attachShape(*shape->PxShape);
}

DLL_EXPORT_API glm::vec3 VCInteropPhysicsRigidActorGetPosition( int handle )
{
	VCPxRigidActor* obj = (VCPxRigidActor*) VCObjectStore::Instance->GetObject(handle);
	physx::PxTransform trans = obj->PxRigidActor->getGlobalPose();
	return glm::vec3(trans.p.x, trans.p.y, trans.p.z);
}

DLL_EXPORT_API glm::vec4 VCInteropPhysicsRigidActorGetRotation( int handle )
{
	VCPxRigidActor* obj = (VCPxRigidActor*) VCObjectStore::Instance->GetObject(handle);
	physx::PxTransform trans = obj->PxRigidActor->getGlobalPose();
	return glm::vec4(trans.q.x, trans.q.y, trans.q.z, trans.q.w);
}
