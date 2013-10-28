//
//  VCCamera.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCGameObject.h"
#include "VCAllPrimitives.h"

class VCCamera : public VCGameObject
{
public:
	VCCamera(void);
	~VCCamera(void);
    
	virtual void PreRender();
	glm::vec3 ScreenPointToDirection( VCRectangle viewPort, VCPoint screenPoint );
    
	float FovDeg;
	float Aspect;
	float NearClip;
	float FarClip;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionViewMatrix;

	glm::mat4 InverseViewMatrix;
    
    VCRectangle Frame;
    
    
    // ================================      Interop      ============
public:
    static void RegisterMonoHandlers();
    
private:
    friend int VCInteropNewCamera();
    friend void VCInteropReleaseCamera(int handle);
    // ===============================================================
};

// Interop
int VCInteropNewCamera();
void VCInteropReleaseCamera(int handle);
glm::vec3 VCInteropCameraScreenPointToDirection(int handle, VCRectangle viewPort, VCPoint screenPoint);
void VCInteropCameraSetFields(int handle, float fovDeg, float aspect, float nearClip, float farClip, VCRectangle frame);
void VCInteropCameraGetFields(int handle, float* fovDeg, float* aspect, float* nearClip, float* farClip, VCRectangle* frame);