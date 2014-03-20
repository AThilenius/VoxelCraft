//
//  VCCamera.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCCamera.h"

#include "VCGLWindow.h"
#include "VCObjectStore.h"


VCCamera* VCCamera::BoundCamera;

VCCamera::VCCamera(void)//:
	//Viewport(VCRectangle(0, 0, 100, 100))
{
    VCObjectStore::Instance->UpdatePointer(Handle, this);
	LightInverseDirection = glm::normalize(glm::vec3(2, 1, 0.5));
}


VCCamera::~VCCamera(void)
{
}

// ================================      Interop      ============
int VCInteropNewCamera()
{
    VCCamera* newCamera = new VCCamera();
    return newCamera->Handle;
}

void VCInteropReleaseCamera(int handle)
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

void VCInteropCameraSetProjectionViewMatrix( int handle, glm::mat4 projMatrix, glm::mat4 viewMatrix )
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);
	obj->ProjectionMatrix = projMatrix;
	obj->ViewMatrix = viewMatrix;
	obj->ProjectionViewMatrix = projMatrix * viewMatrix;
	obj->InverseViewMatrix = glm::inverse(viewMatrix);
}

void VCInteropCameraSetViewport( int handle, VCRectangle viewport )
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);
	obj->Viewport = viewport;
}

void VCInteropCameraSetUpdateState( int handle, bool value )
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);
	obj->WasUpdated = value;
}

// ===============================================================