//
//  VCPxRigidStatic.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCPxRigidActor.h"

class VCPxRigidStatic : public VCPxRigidActor
{
public:
	VCPxRigidStatic();
	~VCPxRigidStatic();

public:
	physx::PxRigidStatic* PxRigidStatic;
	
};

DLL_EXPORT_API int VCInteropPhysicsRigidStaticCreate(glm::vec3 pos, glm::vec4 quat);
DLL_EXPORT_API void VCINteropPhysicsRigidStaticRelease(int handle);