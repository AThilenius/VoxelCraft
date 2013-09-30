//
//  VCPhysics.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/28/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCPhysics.h"


VCPhysics::VCPhysics(void)
{
}


VCPhysics::~VCPhysics(void)
{
}

void VCPhysics::RegisterMonoHandlers()
{
	mono_add_internal_call("VCEngine.Physics::VCInteropPhysicsRaycastWorld", (void*)VCInteropPhysicsRaycastWorld);
}

bool VCInteropPhysicsRaycastWorld(Ray ray, RaycastHit* hitOut)
{
	//printf("Got Ray: %f, %f, %f | %f, %f, %f | %f", ray.Origin.x, ray.Origin.y, ray.Origin.z, ray.Direction.x, ray.Direction.y, ray.Direction.z, ray.MaxDistance);

	//hitOut->Distance = 42.0f;
	//hitOut->Normal = vec3(1, 2, 3);
	//hitOut->Type = Block_Dirt;
	//hitOut->X = 4;
	//hitOut->Y = 2;
	//hitOut->Z = 0;

	//return true;
	bool result = VCPhysics::RaycastWorld(ray, hitOut);
	return result;
}

