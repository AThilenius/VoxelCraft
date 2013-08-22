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


class VCTransform;

class VCTransform : public VCComponent
{
public:
	VCTransform(void);
	~VCTransform(void);

	virtual void PreRender();
	VCTransform* GetParent();
	void SetParent ( VCTransform* parent );

public:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	glm::mat4 ModelMatrix;

private:
	VCTransform* m_parent;
	std::unordered_set<VCTransform*> m_children;

	
};

