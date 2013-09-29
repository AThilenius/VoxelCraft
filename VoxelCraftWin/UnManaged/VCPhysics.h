//
//  VCPhysics.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/28/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include "PCH.h"

typedef struct
{
	bool DidHit;
	double Distance;
	int WorldX;
	int WorldY;
	int WorldZ;

} RaycastHit;

class VCPhysics
{
public:
	VCPhysics(void);
	~VCPhysics(void);

	static bool RaycastWorld(RaycastHit* hit)
	{

	}

    // ================================      Interop      ============
public:
    static void RegisterMonoHandlers();
    // ===============================================================
};

// Interop
void VCInteropPhysicsRaycastWorld(RaycastHit* hitOut);