//
//  VCRenderWindow.cpp
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/28/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "stdafx.h"
#include "VCRenderWindow.h"

#include "VCObjectStore.h"
#include "VCCamera.h"
#include "VCGLRenderer.h"


VCRenderWindow::VCRenderWindow(void)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}

VCRenderWindow::~VCRenderWindow(void)
{

}

void VCRenderWindow::Render()
{
	VCCamera::BoundCamera = Camera;

	for(auto iter = Entities.begin(); iter != Entities.end(); iter++)
	{
		VCEntity* entity = *iter;
		entity->Render(Camera->ProjectionViewMatrix);
	}
}

int VCInteropRenderWindowNew()
{
	VCRenderWindow* rWindow = new VCRenderWindow();
	VCGLRenderer::Instance->AddRenderable(rWindow);
	return rWindow->Handle;
}

void VCInteropRenverIndowRelease( int handle )
{
	VCRenderWindow* obj = (VCRenderWindow*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

void VCInteropRenderWindowSetCamera( int handle, int cameraHandle )
{
	VCRenderWindow* obj = (VCRenderWindow*) VCObjectStore::Instance->GetObject(handle);
	VCCamera* camera = (VCCamera*) VCObjectStore::Instance->GetObject(cameraHandle);
}

void VCInteropRenderWindowAddEntity( int handle, int entityHandle )
{
	VCRenderWindow* obj = (VCRenderWindow*) VCObjectStore::Instance->GetObject(handle);
	VCEntity* entity = (VCEntity*) VCObjectStore::Instance->GetObject(entityHandle);

	obj->Entities.insert(entity);
}

void VCInteropRenderWindowRemoveEntity( int handle, int entityHandle )
{
	VCRenderWindow* obj = (VCRenderWindow*) VCObjectStore::Instance->GetObject(handle);
	VCEntity* entity = (VCEntity*) VCObjectStore::Instance->GetObject(entityHandle);

	obj->Entities.erase(entity);
}
