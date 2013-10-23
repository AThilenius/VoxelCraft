//
//  VCCamera.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCCamera.h"
#include "VCSceneGraph.h"
#include "VCWindow.h"


VCCamera::VCCamera(void):
	FovDeg(65.0f),
	Aspect(4.0f / 3.0f),
	NearClip(0.1f),
	FarClip(400.0f)
{
    VCObjectStore::Instance->UpdatePointer(Handle, this);
	Frame = Rectangle(0, 0, VCWindow::Instance->Width, VCWindow::Instance->Height);
}


VCCamera::~VCCamera(void)
{
}

void VCCamera::PreRender()
{
	Aspect = (float) VCWindow::Instance->Width / (float) VCWindow::Instance->Height;

    // Build ModelMatrix ( This will be the View matrix )
    VCGameObject::PreRender();
    ViewMatrix = ModelMatrix;
	InverseViewMatrix = inverse(ViewMatrix);
    
    // Set Camera's bounds
    //glViewport(Frame.X, Frame.Y, Frame.Width, Frame.Height);
    
	ProjectionMatrix = glm::perspective(FovDeg, Aspect, NearClip, FarClip);
	ProjectionViewMatrix =  ProjectionMatrix * ViewMatrix;
}

vec3 VCCamera::ScreenPointToDirection( Rectangle viewPort, Point screenPoint )
{
	// Convert viewport
	Rectangle screenBounds = VCWindow::Instance->FullViewport;
	vec2 ll (viewPort.X, viewPort.Y);
	vec2 ur (viewPort.X + viewPort.Width, viewPort.Y + viewPort.Height);
	vec2 sp (screenPoint.X, screenPoint.Y);

	vec2 delta = ur - ll;
	vec2 spInViewport (2.0f * sp.x / delta.x - 1.0f, 2.0f * sp.y / delta.y - 1.0f);

	vec4 ray_clip = vec4 (spInViewport.x, spInViewport.y, -1.0f, 1.0f);

	vec4 ray_eye = inverse (ProjectionMatrix) * ray_clip;
	ray_eye = vec4 (ray_eye.x, ray_eye.y, -1.0, 0.0);

	vec4 rayWorld4 = inverse (ViewMatrix) * ray_eye;
	vec3 ray_wor (rayWorld4);
	ray_wor = normalize (ray_wor);

	return ray_wor;
}


// ================================      Interop      ============
void VCCamera::RegisterMonoHandlers()
{
    mono_add_internal_call("VCEngine.Camera::VCInteropNewCamera",						(void*)VCInteropNewCamera);
    mono_add_internal_call("VCEngine.Camera::VCInteropReleaseCamera",					(void*)VCInteropReleaseCamera);
	mono_add_internal_call("VCEngine.Camera::VCInteropCameraScreenPointToDirection",	(void*)VCInteropCameraScreenPointToDirection);
	mono_add_internal_call("VCEngine.Camera::VCInteropCameraSetFields",					(void*)VCInteropCameraSetFields);
	mono_add_internal_call("VCEngine.Camera::VCInteropCameraGetFields",					(void*)VCInteropCameraGetFields);
}

int VCInteropNewCamera()
{
    VCCamera* newCamera = new VCCamera();
    VCSceneGraph::Instance->RegisterCamera(newCamera);
    return newCamera->Handle;
}

void VCInteropReleaseCamera(int handle)
{
    VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);
    delete obj;
}

vec3 VCInteropCameraScreenPointToDirection(int handle, Rectangle viewPort, Point screenPoint)
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);
	return obj->ScreenPointToDirection(viewPort, screenPoint);
}

void VCInteropCameraSetFields(int handle, float fovDeg, float aspect, float nearClip, float farClip, Rectangle frame)
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);

	obj->FovDeg = fovDeg;
	obj->Aspect = aspect;
	obj->NearClip = nearClip;
	obj->FarClip = farClip;
	obj->Frame = frame;
}

void VCInteropCameraGetFields(int handle, float* fovDeg, float* aspect, float* nearClip, float* farClip, Rectangle* frame)
{
	VCCamera* obj = (VCCamera*)VCObjectStore::Instance->GetObject(handle);

	*fovDeg = obj->FovDeg;
	*aspect = obj->Aspect;
	*nearClip = obj->NearClip;
	*farClip = obj->FarClip;
	*frame = obj->Frame;
}
// ===============================================================