//
//  VCBlock.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"

struct VCInteropBlock
{
	VCInteropBlock(): Color(vcint4()) {}
	VCInteropBlock(GLubyte4 color): Color(vcint4(color.x, color.y, color.z, color.w)) {}

	vcint4 Color;
};

class VCBlock
{
public:
	VCBlock(void){}
	VCBlock(VCInteropBlock interopBlock): Color((GLubyte) interopBlock.Color.X, (GLubyte) interopBlock.Color.Y, (GLubyte) interopBlock.Color.Z, (GLubyte) interopBlock.Color.W){}
	VCBlock(GLubyte r, GLubyte g, GLubyte b): Color(GLubyte4(r, g, b, 255)){}
	VCBlock(GLubyte r, GLubyte g, GLubyte b, GLubyte a): Color(GLubyte4(r, g, b, a)){}
	~VCBlock(void){}

	GLubyte4 Color;

	bool IsTrasparent()
	{
		return Color.w == 0;
	}

	bool IsTranslucent()
	{
		return Color.w != 255;
	}

	VCInteropBlock AsInterop()
	{
		return VCInteropBlock(Color);
	}

	// Statics:
	static VCBlock ErrorBlock;
	static VCBlock Air;
};

