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


VCCamera::VCCamera(void)
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
    
    // Set Camera's bounds
    glViewport(Frame.X, Frame.Y, Frame.Width, Frame.Height);
    
    // Build the Projection Matrix ( Can have branchling later )
	ProjectionMatrix = glm::perspective(65.0f, 4.0f / 3.0f, 0.1f, 400.0f);
    
    // Pre-Compute for later use
	ProjectionViewMatrix =  ProjectionMatrix * ViewMatrix;
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