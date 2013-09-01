//
//  VCTransform.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCComponent.h"

class VCGameObject;
class VCTransform;

class VCTransform : public VCComponent
{
public:
	VCTransform(void);
	~VCTransform(void);
    
    virtual void PreRender();
    
public:
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;

	glm::mat4 ModelMatrix;
	
    // ================================      Interop      ============
public:
    int Handle;
    static void RegisterMonoHandlers();
    
private:
    friend int VCInteropNewTransform();
    friend void VCInteropReleaseTransform(int handle);
    
    friend void VCInteropTransformSetPosition(int handle, float x, float y, float z);
    friend void VCInteropTransformSetRotationQuat(int handle, float x, float y, float z, float w);
    friend void VCInteropTransformSetScale(int handle, float x, float y, float z);
    
    friend void VCInteropTransformGetPosition(int handle, float* x, float* y, float* z);
    friend void VCInteropTransformGetRotation(int handle, float* x, float* y, float* z, float* w);
    friend void VCInteropTransformGetScale(int handle, float* x, float* y, float* z);
    // ===============================================================
};

int VCInteropNewTransform();
void VCInteropReleaseTransform(int handle);

void VCInteropTransformSetPosition(int handle, float x, float y, float z);
void VCInteropTransformSetRotationQuat(int handle, float x, float y, float z, float w);
void VCInteropTransformSetScale(int handle, float x, float y, float z);

void VCInteropTransformGetPosition(int handle, float* x, float* y, float* z);
void VCInteropTransformGetRotation(int handle, float* x, float* y, float* z, float* w);
void VCInteropTransformGetScale(int handle, float* x, float* y, float* z);



