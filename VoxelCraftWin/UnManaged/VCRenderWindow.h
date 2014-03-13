//
//  VCRenderWindow.h
//  VoxelCraft
//
//  Created by Alec Thilenius on 12/28/2013.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

class VCCamera;
class VCGLFrameBuffer;

#include "VCMarshalableObject.h"
#include "VCEntity.h"
#include "VCIRenderable.h"

class VCRenderWindow : public VCMarshalableObject
{
public:
	VCRenderWindow();
	~VCRenderWindow();

	void Render();
	void RenderToTexture(VCGLTexture* texture);

public:
	typedef boost::container::flat_set<VCEntity*> FlatEntitySet;

	VCCamera* Camera;
	FlatEntitySet Entities;
};

// CTor / DTor
DLL_EXPORT_API int VCInteropRenderWindowNew();
DLL_EXPORT_API void VCInteropRenverIndowRelease(int handle);

// Rendering
DLL_EXPORT_API void VCInteropRenderWindowRenderToScreen(int handle);
DLL_EXPORT_API void VCInteropRenderWindowRenderToTexture(int handle, int textureHandle);

// Camera
DLL_EXPORT_API void VCInteropRenderWindowSetCamera(int handle, int cameraHandle);

// Entities
DLL_EXPORT_API void VCInteropRenderWindowAddEntity(int handle, int entityHandle);
DLL_EXPORT_API void VCInteropRenderWindowRemoveEntity(int handle, int entityHandle);