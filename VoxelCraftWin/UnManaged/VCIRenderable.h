//
//  VCIRenderable.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "VCRenderState.h"

class VCIRenderable
{
public:

	virtual ~VCIRenderable(void){}
	virtual VCRenderState* GetState() = 0;
	virtual void Render() = 0;
};