//
//  VCPxShape.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 1/11/2014.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCPxShape.h"

#include "VCPxMaterial.h"
#include "VCObjectStore.h"
#include "VCPxPhysics.h"


VCPxShape::VCPxShape(void) :
	PxShape(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCPxShape::~VCPxShape(void)
{
	if (PxShape != NULL)
		PxShape->release();
}

int VCInteropPhysicsBoxShapeNew( int materialHandle, VCFloat3 halfExtent )
{
	VCPxMaterial* material = (VCPxMaterial*)VCObjectStore::Instance->GetObject(materialHandle);

	VCPxShape* vcshape = new VCPxShape();
	vcshape->PxShape = VCPxPhysics::PxPhysics->createShape(physx::PxBoxGeometry(halfExtent.X, halfExtent.Y, halfExtent.Z), *material->PxMaterial);

	return vcshape->Handle;
}

int VCInteropPhysicsCapsuleShapeNew( int materialHandle, float halfRadius, float halfHeight )
{
	VCPxMaterial* material = (VCPxMaterial*)VCObjectStore::Instance->GetObject(materialHandle);

	VCPxShape* vcshape = new VCPxShape();
	vcshape->PxShape = VCPxPhysics::PxPhysics->createShape(physx::PxCapsuleGeometry(halfRadius, halfHeight), *material->PxMaterial);

	return vcshape->Handle;
}

int VCInteropPhysicsPlaneShapeNew( int materialHandle )
{
	VCPxMaterial* material = (VCPxMaterial*)VCObjectStore::Instance->GetObject(materialHandle);

	VCPxShape* vcshape = new VCPxShape();
	vcshape->PxShape = VCPxPhysics::PxPhysics->createShape(physx::PxPlaneGeometry(), *material->PxMaterial);

	return vcshape->Handle;
}

int VCInteropPhysicsSphereShapeNew( int materialHandle, float radius )
{
	VCPxMaterial* material = (VCPxMaterial*)VCObjectStore::Instance->GetObject(materialHandle);

	VCPxShape* vcshape = new VCPxShape();
	vcshape->PxShape = VCPxPhysics::PxPhysics->createShape(physx::PxSphereGeometry(radius), *material->PxMaterial);

	return vcshape->Handle;
}