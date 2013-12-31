//
//  VCCamera.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCGameObject.h"

class VCCamera : public VCGameObject
{
public:
	VCCamera(void);
	~VCCamera(void);

public:
	static VCCamera* BoundCamera;
	VCRectangle Viewport;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionViewMatrix;
	glm::mat4 InverseViewMatrix;
};

// Interop
DLL_EXPORT_API int VCInteropNewCamera();
DLL_EXPORT_API void VCInteropReleaseCamera(int handle);
DLL_EXPORT_API void VCInteropCameraSetProjectionViewMatrix(int handle, glm::mat4 projMatrix, glm::mat4 viewMatrix);
DLL_EXPORT_API void VCInteropCameraSetViewport(int handle, VCRectangle viewport);