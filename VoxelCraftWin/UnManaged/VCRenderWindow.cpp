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
#include "VCGLFrameBuffer.h"


VCRenderWindow::VCRenderWindow(void):
	Camera(NULL)
{
	VCObjectStore::Instance->UpdatePointer(Handle, this);
}

VCRenderWindow::~VCRenderWindow(void)
{

}

void VCRenderWindow::Render()
{
	VCGLFrameBuffer::GetDefault()->Bind();
	glViewport(Camera->Viewport.X, Camera->Viewport.Y, Camera->Viewport.Width, Camera->Viewport.Height);

	// Occlusion Culling code goes here
	for(auto iter = Entities.begin(); iter != Entities.end(); iter++)
	{
		VCEntity* entity = *iter;
		entity->Render(Camera);
	}
}

void VCRenderWindow::RenderToTexture( VCTexture* texture )
{
	VCGLFrameBuffer::GetTextureTarget()->SetRenderTarget(texture);
	VCGLFrameBuffer::GetTextureTarget()->Bind();

	glViewport(Camera->Viewport.X, Camera->Viewport.Y, Camera->Viewport.Width, Camera->Viewport.Height);

	// Occlusion Culling code goes here
	for(auto iter = Entities.begin(); iter != Entities.end(); iter++)
	{
		VCEntity* entity = *iter;
		entity->Render(Camera);
	}
}

int VCInteropRenderWindowNew()
{
	VCRenderWindow* rWindow = new VCRenderWindow();
	return rWindow->Handle;
}

void VCInteropRenverIndowRelease( int handle )
{
	VCRenderWindow* obj = (VCRenderWindow*) VCObjectStore::Instance->GetObject(handle);
	delete obj;
}

void VCInteropRenderWindowRenderToScreen( int handle )
{
	VCRenderWindow* obj = (VCRenderWindow*) VCObjectStore::Instance->GetObject(handle);
	obj->Render();
}

void VCInteropRenderWindowRenderToTexture( int handle, int textureHandle )
{
	VCRenderWindow* obj = (VCRenderWindow*) VCObjectStore::Instance->GetObject(handle);
	VCTexture* texture = (VCTexture*) VCObjectStore::Instance->GetObject(textureHandle);
	obj->RenderToTexture(texture);
}

void VCInteropRenderWindowSetCamera( int handle, int cameraHandle )
{
	VCRenderWindow* obj = (VCRenderWindow*) VCObjectStore::Instance->GetObject(handle);
	VCCamera* camera = (VCCamera*) VCObjectStore::Instance->GetObject(cameraHandle);
	obj->Camera = camera;
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
