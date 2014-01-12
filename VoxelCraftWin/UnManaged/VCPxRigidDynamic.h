//
//  VCPxRigidDynamic.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCGameObject;

#include "VCPxRigidActor.h"

class VCPxRigidDynamic : public VCPxRigidActor
{
public:
	VCPxRigidDynamic(void);
	~VCPxRigidDynamic();

public:
	physx::PxRigidDynamic* PxRigidDynamic;
};

DLL_EXPORT_API int VCInteropPhysicsRigidDynamicCreate(glm::vec3 pos, glm::vec4 quat);
DLL_EXPORT_API void VCINteropPhysicsRigidDynamicRelease(int handle);