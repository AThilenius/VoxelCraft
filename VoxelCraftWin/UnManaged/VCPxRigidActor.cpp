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
