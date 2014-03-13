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
#include "VCPxRigidActor.h"

physx::PxDefaultCpuDispatcher* VCPxScene::m_defaultCpuDispatcher;
physx::PxSimulationFilterShader VCPxScene::m_defaultFilterShader = physx::PxDefaultSimulationFilterShader;

VCPxScene::VCPxScene(void):
	PxScene(NULL),
	FixedDeltaTime(0.01)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCPxScene::~VCPxScene(void)
{
	if (PxScene != NULL)
	{
		PxScene->release();
		PxScene = NULL;
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

	PxScene = VCPxPhysics::PxPhysics->createScene(sceneDesc);

	if (!PxScene)
	{
		VC_ERROR("Failed to create Px Scene.");
	}

	PxScene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE,     1.0);
	PxScene->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);

	VCLog::Info("PxScene Created.", "Physics");
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

void VCInteropPhysicsPxSceneAddActor( int handle, int actorHandle )
{
	VCPxScene* obj = (VCPxScene*)VCObjectStore::Instance->GetObject(handle);
	VCPxRigidActor* actor = (VCPxRigidActor*)VCObjectStore::Instance->GetObject(actorHandle);

	obj->PxScene->addActor(*actor->PxRigidActor);
}

void VCInteropPhysicsPxSceneSimulate(int handle, double deltaTime)
{
	VCPxScene* obj = (VCPxScene*)VCObjectStore::Instance->GetObject(handle);

	while ( deltaTime >= obj->FixedDeltaTime )
	{
		obj->PxScene->simulate(obj->FixedDeltaTime);
		obj->PxScene->fetchResults(true);
		deltaTime -= obj->FixedDeltaTime;
	}
}
