//
//  VCGameObject.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCMarshalableObject.h"

class VCGameObject : public VCMarshalableObject
{
public:
	virtual ~VCGameObject(void) {}
    	
public:
    glm::mat4 ModelMatrix;
};

DLL_EXPORT_API void VCInteropGameObjectSetModelMatrix(int handle, glm::mat4 matrix);