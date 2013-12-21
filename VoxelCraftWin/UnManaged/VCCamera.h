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
    
	virtual void PreRender();
	glm::vec3 ScreenPointToDirection( VCRectangle viewPort, VCPoint screenPoint );

public:
	static VCCamera* BoundCamera;
	float FovDeg;
	float Aspect;
	float NearClip;
	float FarClip;
	bool Orthographic;
	float OrthoWidth;
	float OrthoHeight;
	bool FullScreen;
	VCRectangle Viewport;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionViewMatrix;
	glm::mat4 InverseViewMatrix;
};

// Interop
DLL_EXPORT_API int VCInteropNewCamera();
DLL_EXPORT_API void VCInteropReleaseCamera(int handle);
DLL_EXPORT_API glm::vec3 VCInteropCameraScreenPointToDirection(int handle, VCRectangle viewPort, VCPoint screenPoint);
DLL_EXPORT_API void VCInteropCameraSetFields(int handle, float fovDeg, float aspect, float nearClip, float farClip, VCRectangle viewport, int fullscreen);
DLL_EXPORT_API void VCInteropCameraGetFields(int handle, float* fovDeg, float* aspect, float* nearClip, float* farClip, VCRectangle* viewport, int* fullscreen);