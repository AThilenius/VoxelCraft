//
//  VCPxPhysics.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PxPhysicsAPI.h"

class VCPxPhysics
{
public:

	static void Initialize();

private:
	VCPxPhysics();
	~VCPxPhysics();

public:
	static physx::PxFoundation* PxFoundation;
	static physx::PxProfileZoneManager* PxProfileZoneManager;
	static physx::PxPhysics* PxPhysics;
	static physx::PxCudaContextManager* CudaContextManager;

private:
	static physx::PxDefaultErrorCallback m_defaultErrorCallback;
	static physx::PxDefaultAllocator m_defaultAllocatorCallback;
};

DLL_EXPORT_API void VCInteropPhysicsInitializePhysXPhysics();