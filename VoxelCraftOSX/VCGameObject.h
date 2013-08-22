//
//  VCGameObject.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCComponent.h"

class VCTransform;

// Container class for any game object.
class VCGameObject : public VCComponent
{
public:
	VCGameObject(void);
	~VCGameObject(void);

	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Gui();
	virtual void PreRender();

	void AttachComponent ( VCComponent* component );

private:
	std::unordered_set<VCComponent*> m_components;
};

