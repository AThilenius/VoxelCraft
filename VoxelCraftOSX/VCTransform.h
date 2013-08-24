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
	
};

