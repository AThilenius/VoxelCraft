//
//  VCGLRenderer.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCVoxelShader.h"
#include "VCCamera.h"

class VCGLRenderer
{
public:
	VCGLRenderer(void);
	~VCGLRenderer(void);

	void Initialize();
	void Render();

	static VCVoxelShader* VoxelShader;

};

