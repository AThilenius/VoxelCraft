//
//  VCRenderStage.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#include "VCRenderStage.h"


VCRenderStage::VCRenderStage(void):
	FrameBuffer(0),
	Shader(NULL),
	Blend(true),
	DepthTest(true)
{
	for ( int i = 0; i < MAX_TEXTURES; i++ )
		Textures[i] = 0;
}


VCRenderStage::~VCRenderStage(void)
{
}
