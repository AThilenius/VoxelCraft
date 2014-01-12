//
//  VCPxRigedActor.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCMarshalableObject.h"
#include "PxPhysicsAPI.h"

class VCPxRigidActor : public VCMarshalableObject
{
public:
	VCPxRigidActor();
	~VCPxRigidActor();

public:
	physx::PxRigidActor* PxRigidActor;
};

DLL_EXPORT_API void VCInteropPhysicsRigidActorAttachShape(int handle, int shapeHandle);