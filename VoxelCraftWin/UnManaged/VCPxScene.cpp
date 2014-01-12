//
//  VCPxScene.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPxScene.h"
#include "VCPxPhysics.h"
#include "extensions\PxDefaultSimulationFilterShader.h"
#include "VCObjectStore.h"

physx::PxDefaultCpuDispatcher* VCPxScene::m_defaultCpuDispatcher;
physx::PxSimulationFilterShader VCPxScene::m_defaultFilterShader = physx::PxDefaultSimulationFilterShader;

VCPxScene::VCPxScene(void):
	m_scene(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCPxScene::~VCPxScene(void)
{
	if (m_scene != NULL)
	{
		m_scene->release();
		m_scene = NULL;
	}
}

void VCPxScene::Initialize()
{
	physx::PxSceneDesc sceneDesc(VCPxPhysics::PxPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);

	if(!sceneDesc.cpuDispatcher)
	{
		m_defaultCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(8);

		if(!m_defaultCpuDispatcher)
		{
			VC_ERROR("PxDefaultCpuDispatcherCreate failed!");
		}

		sceneDesc.cpuDispatcher = m_defaultCpuDispatcher;
	}

	if(!sceneDesc.filterShader)
		sceneDesc.filterShader = m_defaultFilterShader;

#ifdef PX_WINDOWS
	if(!sceneDesc.gpuDispatcher && VCPxPhysics::CudaContextManager)
		sceneDesc.gpuDispatcher = VCPxPhysics::CudaContextManager->getGpuDispatcher();
#endif

	std::cout << "PxScene Created." << std::endl;
}

int VCInteropPhysicsPxSceneNew()
{
	VCPxScene* scene = new VCPxScene();
	scene->Initialize();
	return scene->Handle;
}

void VCInteropPhysicsPxSceneRelease( int handle )
{
	VCPxScene* obj = (VCPxScene*)VCObjectStore::Instance->GetObject(handle);
	delete obj;
}
