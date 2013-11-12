//
//  VCCamera.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCCamera.h"

#include "VCSceneGraph.h"
#include "VCWindow.h"
#include "VCObjectStore.h"
#include "VCMonoRuntime.h"


VCCamera::VCCamera(void):
	FovDeg(65.0f),
	Aspect(4.0f / 3.0f),
	NearClip(0.1f),
	FarClip(400.0f),
	Orthographic(false),
	OrthoHeight(1.0f),
	OrthoWidth(1.0f),
	FullScreen(true),
	Viewport(VCRectangle(0, 0, VCWindow::Instance->Width, VCWindow::Instance->Height))
{
    VCObjectStore::Instance->UpdatePointer(Handle, this);
}


VCCamera::~VCCamera(void)
{
}

void VCCamera::PreRender()
{
	// Viewport
	if (FullScreen)
		Viewport = VCRectangle(0, 0, VCWindow::Instance->Width, VCWindow::Instance->Height);

    // View Matrix ( Using the Model Matrix for this GameObject )
    VCGameObject::PreRender();
    ViewMatrix = ModelMatrix;
	InverseViewMatrix = glm::inverse(ViewMatrix);
    
	// Projection Matrix
	if (Orthographic)
		ProjectionMatrix = glm::ortho<float>(-OrthoWidth * 0.5f, OrthoWidth * 0.5f, -OrthoHeight * 0.5f, OrthoHeight * 0.5f, NearClip, FarClip);

	else
		ProjectionMatrix = glm::perspective(FovDeg, Aspect, NearClip, FarClip);

	ProjectionViewMatrix =  ProjectionMatrix * ViewMatrix;
}

glm::vec3 VCCamera::ScreenPointToDirection( VCRectangle viewPort, VCPoint screenPoint )
{
	// Convert viewport
	VCRectangle screenBounds = VCWindow::Instance->FullViewport;
	glm::vec2 ll (viewPort.X, viewPort.Y);
	glm::vec2 ur (viewPort.X + viewPort.Width, viewPort.Y + viewPort.Height);
	glm::vec2 sp (screenPoint.X, screenPoint.Y);

	glm::vec2 delta = ur - ll;
	glm::vec2 spInViewport (2.0f * sp.x / delta.x - 1.0f, 2.0f * sp.y / delta.y - 1.0f);

	glm::vec4 ray_clip = glm::vec4 (spInViewport.x, spInViewport.y, -1.0f, 1.0f);

	glm::vec4 ray_eye = glm::inverse (ProjectionMatrix) * ray_clip;
	ray_eye = glm::vec4 (ray_eye.x, ray_eye.y, -1.0, 0.0);

	glm::vec4 rayWorld4 = glm::inverse (ViewMatrix) * ray_eye;
	glm::vec3 ray_wor (rayWorld4);
	ray_wor = glm::normalize (ray_wor);

	return ray_wor;
}


// ================================      Interop      ============
void VCCamera::RegisterMonoHandlers()
{
    VCMonoRuntime::SetMethod("Camera::VCInteropNewCamera",							(void*)VCInteropNewCamera);
    VCMonoRuntime::SetMethod("Camera::VCInteropReleaseCamera",						(void*)VCInteropReleaseCamera);
	VCMonoRuntime::SetMethod("Camera::VCInteropCameraScreenPointToDirection",		(void*)VCInteropCameraScreenPointToDirection);
	VCMonoRuntime::SetMethod("Camera::VCInteropCameraSetFields",					(void*)VCInteropCameraSetFields);
	VCMonoRuntime::SetMethod("Camera::VCInteropCameraGetFields",					(void*)VCInteropCameraGetFields);
}

int VCInteropNewCamera()
{
	VC_ERROR("VCInteropNewCamera() Deprecated.")
    VCCamera* newCamera = new VCCamera();
    return newCamera->Handle;
}

void VCInteropReleaseCamera(int handle)
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

glm::vec3 VCInteropCameraScreenPointToDirection(int handle, VCRectangle viewPort, VCPoint screenPoint)
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);
	return obj->ScreenPointToDirection(viewPort, screenPoint);
}

void VCInteropCameraSetFields(int handle, float fovDeg, float aspect, float nearClip, float farClip, VCRectangle viewport, int fullscreen)
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);

	obj->FovDeg = fovDeg;
	obj->Aspect = aspect;
	obj->NearClip = nearClip;
	obj->FarClip = farClip;
	obj->Viewport = viewport;
	obj->FullScreen = fullscreen > 0;
}

void VCInteropCameraGetFields(int handle, float* fovDeg, float* aspect, float* nearClip, float* farClip, VCRectangle* viewport, int* fullscreen)
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);

	*fovDeg = obj->FovDeg;
	*aspect = obj->Aspect;
	*nearClip = obj->NearClip;
	*farClip = obj->FarClip;
	*viewport = obj->Viewport;
	*fullscreen = obj->FullScreen ? 1 : 0;
}
// ===============================================================