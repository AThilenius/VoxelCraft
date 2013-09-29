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

void VCInteropPhysicsRaycastWorld(RaycastHit* hitOut)
{
	hitOut->DidHit = true;
	hitOut->Distance = 42.0f;
	hitOut->WorldX = 4;
	hitOut->WorldY = 2;
	hitOut->WorldZ = 0;
}

