//
//  VCBlock.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"


class VCBlock
{
public:
	VCBlock(void){}
	VCBlock(GLubyte r, GLubyte g, GLubyte b): Color(GLubyte4(r, g, b, 255)){}
	VCBlock(GLubyte r, GLubyte g, GLubyte b, GLubyte a): Color(GLubyte4(r, g, b, a)){}
	~VCBlock(void){}

	GLubyte4 Color;

	bool IsTrasparent()
	{
		return Color.w != 255;
	}

	// Statics:
	static VCBlock ErrorBlock;
	static VCBlock Air;
};

