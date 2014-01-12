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
	VCPxRigidDynamic(VCFloat3 pos, VCFloat4 rot);
	~VCPxRigidDynamic();

public:
	physx::PxRigidDynamic* PxRigidDynamic;
};
