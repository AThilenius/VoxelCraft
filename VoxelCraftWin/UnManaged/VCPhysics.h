//
//  VCPhysics.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/28/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCBlock.h"

struct Ray
{
	Ray();
	Ray(glm::vec3 origin, glm::vec3 direction, float maxDist);
	glm::vec3 Origin;
	glm::vec3 Direction;
	float MaxDistance;
};

struct RaycastHit
{
	float Distance;
	VCBlock Type;
	glm::vec3 Normal;
	int X, Y, Z;
};