//
//  VCComponent.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"

class VCTransform;
class VCGameObject;

class VCComponent
{
public:
	VCComponent(void);
	~VCComponent(void);

	bool Enabled;

	VCGameObject* GameObject;
	VCTransform* Transform;

	virtual void Start() { };
	virtual void Update() { };
	virtual void LateUpdate() { };
	virtual void Gui() { };
	virtual void PreRender() { };


};

