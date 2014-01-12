//
//  VCPxPhysics.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPxPhysics.h"

#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultErrorCallback.h"
#include "extensions/pxdefaultallocator.h"
#include "common/PxTolerancesScale.h"

physx::PxFoundation* VCPxPhysics::PxFoundation = NULL;
physx::PxProfileZoneManager* VCPxPhysics::PxProfileZoneManager = NULL;
physx::PxPhysics* VCPxPhysics::PxPhysics = NULL;
physx::PxCudaContextManager* VCPxPhysics::CudaContextManager;

physx::PxDefaultErrorCallback VCPxPhysics::m_defaultErrorCallback;
physx::PxDefaultAllocator VCPxPhysics::m_defaultAllocatorCallback;

void VCPxPhysics::Initialize()
{
	// =====   Foundation   ======================================================
	PxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_defaultAllocatorCallback, m_defaultErrorCallback);

	if(!PxFoundation)
	{
		VC_ERROR("Failed to create a PhysX foundation.");
	}

	// =====   Profiler Zone Manager   ======================================================
	PxProfileZoneManager = &physx::PxProfileZoneManager::createProfileZoneManager(PxFoundation);
	if(!PxProfileZoneManager)
	{
		VC_ERROR("PxProfileZoneManager::createProfileZoneManager failed!");
	}

	// =====   CUDA Context Manager   ======================================================
#ifdef PX_WINDOWS

	physx::PxCudaContextManagerDesc cudaContextManagerDesc;
	CudaContextManager = physx::PxCreateCudaContextManager(*PxFoundation, cudaContextManagerDesc, PxProfileZoneManager);

	if (CudaContextManager)
	{
		if (!CudaContextManager->contextIsValid())
		{
			CudaContextManager->release();
			CudaContextManager = NULL;
			VC_WARN("Invalid Px Cuda Context, defaulting to CPU dispatching.");
		}
	}

	else
		VC_WARN("Failed to create a Px Cuda Context, defaulting to CPU dispatching.");

#endif

	// =====   Physics   ======================================================
	bool recordMemoryAllocations = true;
	PxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *PxFoundation, physx::PxTolerancesScale(), recordMemoryAllocations, PxProfileZoneManager );
	if(!PxPhysics)
	{
		VC_ERROR("PxCreatePhysics failed!");
	}

	// =====   Extensions   ======================================================
	if (!PxInitExtensions(*PxPhysics))
	{
		VC_ERROR("PxInitExtensions failed!");
	}

	std::cout << "VCPxPhysics Initialized." << std::endl;
}

void VCInteropPhysicsInitializePhysXPhysics()
{
	VCPxPhysics::Initialize();
}
