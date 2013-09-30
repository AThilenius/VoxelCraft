//
//  VCCamera.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCGameObject.h"

class VCSceneGraph;

class VCCamera : public VCGameObject
{
public:
	VCCamera(void);
	~VCCamera(void);
    
	virtual void PreRender();
	vec3 ScreenPointToRay( int x, int y );
    
	float FovDeg;
	float Aspect;
	float NearClip;
	float FarClip;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionViewMatrix;

	glm::mat4 InverseViewMatrix;
    
    Rectangle Frame;
    
    
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
vec3 VCInteropCameraScreenPointToRay(int handle, int x, int y);
void VCInteropCameraSetFields(int handle, float fovDeg, float aspect, float nearClip, float farClip, Rectangle frame);
void VCInteropCameraGetFields(int handle, float* fovDeg, float* aspect, float* nearClip, float* farClip, Rectangle* frame);