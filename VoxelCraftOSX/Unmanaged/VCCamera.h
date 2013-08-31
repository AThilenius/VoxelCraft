//
//  VCCamera.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#import "PCH.h"
#import "VCComponent.h"
#import "VCTransform.h"

class VCSceneGraph;

class VCCamera : public VCComponent
{
public:
	VCCamera(void);
	~VCCamera(void);

	virtual void PreRender();

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionViewMatrix;
    
public:
    Rectangle Frame;

    
    // ================================      Interop      ============
public:
    int Handle;
    static void RegisterMonoHandlers();
    
private:
    friend int VCInteropNewCamera();
    friend void VCInteropReleaseCamera(int handle);
    // ===============================================================
};

// Interop
int VCInteropNewCamera();
void VCInteropReleaseCamera(int handle);