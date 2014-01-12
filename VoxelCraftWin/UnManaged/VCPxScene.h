//
//  VCPxScene.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/10/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultSimulationFilterShader.h"
#include "VCMarshalableObject.h"

class VCPxScene : public VCMarshalableObject
{
public:
	VCPxScene();
	~VCPxScene();

	void Initialize();

private:
	static physx::PxDefaultCpuDispatcher* m_defaultCpuDispatcher;
	static physx::PxSimulationFilterShader m_defaultFilterShader;
	physx::PxScene* m_scene;
	
};

DLL_EXPORT_API int VCInteropPhysicsPxSceneNew();
DLL_EXPORT_API void VCInteropPhysicsPxSceneRelease(int handle);
