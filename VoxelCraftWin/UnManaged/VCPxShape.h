//
//  VCPxShape.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/11/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCMarshalableObject.h"
#include "PxPhysicsAPI.h"

class VCPxShape : public VCMarshalableObject
{
public:
	VCPxShape();
	~VCPxShape();

	physx::PxShape* PxShape;
	
};

DLL_EXPORT_API int VCInteropPhysicsBoxShapeNew(int materialHandle, VCFloat3 halfExtent);
DLL_EXPORT_API int VCInteropPhysicsCapsuleShapeNew(int materialHandle, float halfRadius, float halfHeight);
DLL_EXPORT_API int VCInteropPhysicsPlaneShapeNew(int materialHandle);
DLL_EXPORT_API int VCInteropPhysicsSphereShapeNew(int materialHandle, float radius);
DLL_EXPORT_API void VCInteropPhysicsShapeRelease(int handle);