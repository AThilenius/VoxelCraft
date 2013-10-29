//
//  VCBlock.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/20/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct VCInteropBlock
{
	VCInteropBlock();
	VCInteropBlock(GLubyte4 color);

	vcint4 Color;
};

class VCBlock
{
public:
	VCBlock(void);
	VCBlock(VCInteropBlock interopBlock);
	VCBlock(GLubyte r, GLubyte g, GLubyte b);
	VCBlock(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	~VCBlock(void);

	bool IsTrasparent();
	bool IsTranslucent();
	VCInteropBlock AsInterop();

	// Statics:
	static VCBlock ErrorBlock;
	static VCBlock Air;

	GLubyte4 Color;
};