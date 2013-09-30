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
    cout << "VCCamera created with handle: " << Handle << endl;
    
	Frame = Rectangle(0, 0, VCWindow::Instance->Width, VCWindow::Instance->Height);
}


VCCamera::~VCCamera(void)
{
}

void VCCamera::PreRender()
{
    // Build ModelMatrix ( This will be the View matrix )
    VCGameObject::PreRender();
    ViewMatrix = ModelMatrix;
	InverseViewMatrix = inverse(ViewMatrix);
    
    // Set Camera's bounds
    glViewport(Frame.X, Frame.Y, Frame.Width, Frame.Height);
    
    // Build the Projection Matrix ( Can have branchling later )
	ProjectionMatrix = glm::perspective(FovDeg, Aspect, NearClip, FarClip);
    
    // Pre-Compute for later use
	ProjectionViewMatrix =  ProjectionMatrix * ViewMatrix;
}

// Algorithm from:
// http://www.mvps.org/directx/articles/rayproj.htm
vec3 VCCamera::ScreenPointToRay( int x, int y )
{
	float dx,dy;

	dx=tanf(FovDeg * 0.0174532925f * 0.5f) * ( x / Frame.Width * 0.5f - 1.0f ) / Aspect ;
	dy=tanf(FovDeg * 0.0174532925f * 0.5f) * ( 1.0f - y / Frame.Height * 0.5f );

	vec3 p1 = vec3( dx * NearClip, dy * NearClip, NearClip);
	vec3 p2 = vec3( dx * FarClip, dy * FarClip, FarClip);

	vec4 t1 = InverseViewMatrix * vec4(p1.x, p1.y, p1.z, 1);
	vec4 t2 = InverseViewMatrix * vec4(p2.x, p2.y, p2.z, 1);

	vec3 delta = vec3(t2) - vec3(t1);
	delta = normalize(delta);

	return delta;
}


// ================================      Interop      ============
void VCCamera::RegisterMonoHandlers()
{
    mono_add_internal_call("VCEngine.Camera::VCInteropNewCamera",         (void*)VCInteropNewCamera);
    mono_add_internal_call("VCEngine.Camera::VCInteropReleaseCamera",     (void*)VCInteropReleaseCamera);
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
// ===============================================================