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
    
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionViewMatrix;
    
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